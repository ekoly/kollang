#include <string>
#include <set>
#include <vector>

#include "KolObj.h"
#include "KolScopes.h"
#include "KolOverhead.h"
#include "KolParse.h"

KolToken *parsevar(string &expr, int &start) {

    string buffer;
    char c;

    for (int j = start; j < expr.size(); j++) {
        c = expr[j];
        if ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || '0' <= c && c <= '9' || c == '_') {
            buffer.push_back(c);
        } else {
            start = j;
            break;
        }
    }

    KolObject *result = (KolObject *)kolScopeLookup(buffer);
    if (result != NULL) {
        return result;
    }

    return new KolObject();

}

KolToken *parsestring(string &expr, int *start) {

    #if DEBUG == 1
    cout << "parsestring()" << *start << "\n";
    #endif

    string buffer;
    int j = (*start)+1;

    char c, lookahead;
    char bound = expr[*start];

    while (j < expr.length()) {

        c = expr[j];

        if (c == '\\') {

            if (j+1 >= expr.length()) {
                return NULL;
            }

            lookahead = expr[j+1];
            switch (lookahead) {
                case 'n':
                    buffer.push_back('\n');
                    break;
                case 't':
                    buffer.push_back('\t');
                    break;
                case '\'':
                    buffer.push_back('\'');
                    break;
                case '"':
                    buffer.push_back('"');
                    break;
                case '\\':
                    buffer.push_back('\\');
                    break;
                default:
                    return NULL;
            }

            j += 2;

        } else if (c == bound) {
            break;
        } else {
            buffer.push_back(c);
            j++;
        }

    }

    *start = j+1;

    return new KolString(buffer);

}

KolToken *parsenumber(string &expr, int *start) {

    string buffer;
    int j = *start;
    bool is_float = false;

    while (j < expr.length() && (('0' <= expr[j] && expr[j] <= '9') || expr[j] == '.' || expr[j] == '_')) {
        if (expr[j] == '.' && is_float) {
            return NULL;
        } else if (expr[j] == '.' && !is_float) {
            is_float = true;
            buffer.push_back(expr[j]);
        } else if ('0' <= expr[j] && expr[j] <= '9') {
            buffer.push_back(expr[j]);
        }
        j++;
    }

    *start = j;

    if (is_float) {
        return new KolFloat(stof(buffer));
    } else {
        return new KolInt(stoi(buffer));
    }

}

KolToken *parseset(string &expr, int *start) {
    return NULL;
}

KolToken *parsetuple(string &expr, int *start) {

    string buffer, parens;
    int j = (*start)+1,
        exprstart = 0;
    char c;

    while (j < expr.length()) {

        c = expr[j];

        switch (c) {

            case '(':
            case '{':
            case '[':
                parens.push_back(c);
                buffer.push_back(c);
                break;

            case ')':
                if (parens.empty()) {
                    *start = j+1;
                    return parseexpr(buffer, &exprstart);
                }
            case '}':
            case ']':
                if (parens.empty() || parens.back() != c) {
                    return NULL;
                } else {
                    parens.pop_back();
                    buffer.push_back(c);
                }
                break;

            default:
                buffer.push_back(c);
                break;

        }
    }

    return NULL;

}

KolToken *parselist(string &expr, int *start) {
    return NULL; // TODO
}

KolToken *parseexpr(string &expr, int *start) {

    #if DEBUG == 1
    cout << "parseexpr()" << "\n";
    #endif

    int j = *start;
    vector<KolToken *> tokens;

    auto cmp = [](KolOperator *a, KolOperator *b) {
        return a->getPrecedence() < b->getPrecedence();
    };
    set<KolOperator *, decltype(cmp)> ops(cmp);
    vector<pair<string, KolOperator *>> *operators = getKolOperators();

    char c, lookahead;
    bool is_continue;

    while (expr[j] == ' ') {
        if (j+1 >= expr.size()) {
            return NULL;
        }
        j++;
    }

    while (j < expr.length()) {

        is_continue = false;
        c = expr[j];

        if (tokens.size() > 0) {
            #if DEBUG == 1
            cout << tokens.back()->getClassname() << ", " << c << "\n";
            #endif
        }

        if (j+1 < expr.length()) {
            lookahead = expr[j+1];
        } else {
            lookahead = ' ';
        }

        if (c == ' ') {
            j++;
            continue;
        } else if (('0' <= c && c <= '9') || (c == '.' && '0' <= lookahead && lookahead <= '9')) {
            tokens.push_back(parsenumber(expr, &j));
            if (tokens.back() == NULL) {
                return NULL;
            }
            continue;
        } else if (c == '\'' || c == '"') {
            tokens.push_back(parsestring(expr, &j));
            if (tokens.back() == NULL) {
                return NULL;
            }
            continue;
        }

        for (vector<pair<string, KolOperator *>>::iterator it = operators->begin(); it != operators->end(); it++) {
            string kop = it->first;
            if (j+kop.length() >= expr.length()) {
                continue;
            }
            if (expr.compare(j, kop.length(), kop) == 0) {
                tokens.push_back(it->second);
                ops.insert(it->second);
                j += kop.length();
                is_continue = true;
                break;
            }
        }

        if (is_continue) {
            continue;
        }

        if ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || c == '_') {
            tokens.push_back(parsevar(expr, j));
            if (tokens.back() == NULL) {
                return NULL;
            }
        } else if (c == '(') {
            tokens.push_back(parsetuple(expr, &j));
            if (tokens.back() == NULL) {
                return NULL;
            }
        } else if (c == '[') {
            tokens.push_back(parselist(expr, &j));
            if (tokens.back() == NULL) {
                return NULL;
            }
        } else if (c == '{') {
            tokens.push_back(parseset(expr, &j));
            if (tokens.back() == NULL) {
                return NULL;
            }
        }
    }

    *start = j+1;
    #if DEBUG == 1
    cout << "num tokens: " << tokens.size() << "\n";
    #endif

    bool is_using_prev;
    vector<KolToken *> next_tokens;

    for (set<KolOperator *>::iterator it = ops.begin(); it != ops.end(); it++) {

        next_tokens = vector<KolToken *>();
        KolOperator *kop = *it;
        KolObject *self, *callback, *result;
        is_using_prev = false;
        int max_arg = 0;

        #if DEBUG == 1
        cout << "processing op: " << kop->getClassname() << "\n";
        #endif

        if (kop->getSelf() == -1) {
            is_using_prev = true;
        }

        vector<int> &args = kop->getArgs();
        for (int k = 0; k < args.size(); k++) {
            if (args[k] == -1) {
                is_using_prev = true;
            }
            if (args[k] > max_arg) {
                max_arg = args[k];
            }
        }

        for (int j = 0; j < tokens.size(); j++) {
            KolToken *kt = tokens[j];

            #if DEBUG == 1
            cout << "processing token: " << kt->getClassname() << "\n";
            #endif

            if (kt == kop) {
                if (kop->getSelf() == -1) {
                    self = (KolObject *)next_tokens.back();
                    next_tokens.pop_back();
                    #if DEBUG == 1
                    cout << "self is previous token: " << self->getClassname() << "." << kop->getDunder() << "\n";
                    #endif
                    callback = self->access(kop->getDunder());
                } else if (kop->getSelf() == 0) {
                    self = NULL;
                    callback = scopes[0].find(kop->getDunder())->second;
                } else {
                    self = (KolObject *)tokens[j + kop->getSelf()];
                    callback = self->access(kop->getDunder());
                }

                #if DEBUG == 1
                cout << "callback: " << callback << "\n";
                #endif

                vector<KolObject *> arg_objs = {self};
                for (int k = 0; k < args.size(); k++) {
                    if (args[k] == -1) {
                        arg_objs.push_back((KolObject *)next_tokens.back());
                        next_tokens.pop_back();
                    } else {
                        arg_objs.push_back((KolObject *)tokens[j + args[k]]);
                    }
                }

                result = ((KolFunction *)callback)->call(arg_objs);
                next_tokens.push_back(result);

                j += max_arg;

            } else {
                next_tokens.push_back(kt);
            }

        }

        tokens = next_tokens;

    }

    return tokens[0];

}

int parseline(string &line) {

    #if DEBUG == 1
    cout << "parsing line: " << line << '\n';
    #endif
    vector<KolToken *> tokens;
    int i = 0;

    while (i < line.size()) {
        KolToken *t = parseexpr(line, &i);
        tokens.push_back(t);
    }

    for (int j = 0; j < tokens.size(); j++) {
        vector<KolObject *> args;
        args.push_back((KolObject *)tokens[j]);
        KolFunction *callback = (KolFunction *)((KolObject *)tokens[j])->access("__str__");
        KolString *res = (KolString *)callback->call(args);
        #if DEBUG == 1
        cout << res->getValue() << '\n';
        #endif
    }

    return 0;

}

int parse(ifstream &source) {

    char c;
    string buffer;
    string parens;

    int line_number = 1;

    while (source) {
       c = source.get();
       switch (c) {
           case '\n':
               if (parens.length() > 0) {
                   buffer.push_back(' ');
               } else {
                   parseline(buffer);
                   buffer.clear();
               }
               line_number++;
               continue;

           case ';':
               if (parens.length() > 0) {
                   #if DEBUG == 1
                   cout << "\nMismatched parens on line " << line_number << "\n";
                   #endif
                   return 1;
               } else {
                   parseline(buffer);
                   buffer.clear();
               }
               continue;

           case '(':
           case '[':
           case '{':
               parens.push_back(c);
               buffer.push_back(c);
               continue;

           case ')':
               if (parens.back() != '(') {
                   #if DEBUG == 1
                   cout << "\nMismatched parens on line " << line_number << "\n";
                   #endif
                   return 1;
               }
               parens.pop_back();
               buffer.push_back(c);
               continue;

           case ']':
               if (parens.back() != ']') {
                   #if DEBUG == 1
                   cout << "\nMismatched square brackets on line " << line_number << "\n";
                   #endif
                   return 1;
               }
               parens.pop_back();
               buffer.push_back(c);
               continue;

           case '}':
               if (parens.back() != '}') {
                   #if DEBUG == 1
                   cout << "\nMismatched curley braces on line " << line_number << "\n";
                   #endif
                   return 1;
               }
               parens.pop_back();
               buffer.push_back(c);
               continue;

           default:
               buffer.push_back(c);
               continue;
       }
    }

    parseline(buffer);

    return 0;

}
