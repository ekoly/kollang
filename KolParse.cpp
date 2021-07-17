#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include "KolMain.h"
#include "KolObj.h"
#include "KolScopes.h"
#include "KolOverhead.h"
#include "KolParse.h"

KolToken *parsevar(string &expr, unsigned *start) {

    string buffer;
    char c;
    unsigned j;

    for (j = *start; j < expr.size(); j++) {
        c = expr[j];
        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == '_') {
            buffer.push_back(c);
        } else {
            break;
        }
    }

    *start = j;

    return new KolUnboundVariable(buffer);

}

KolToken *parsestring(string &expr, unsigned *start) {

    #if DEBUG >= 1
    cout << "parsestring()" << *start << "\n";
    #endif

    string buffer;
    unsigned j = (*start)+1;

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

KolToken *parsenumber(string &expr, unsigned *start) {

    string buffer;
    unsigned j = *start;
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

KolToken *parseset(string &expr, unsigned *start) {
    return NULL;
}

KolToken *parsetuple(string &expr, unsigned *start) {

    #if DEBUG >= 1
    cout << "parsetuple()\n";
    #endif

    string buffer, parens;
    unsigned j = (*start)+1,
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
                    cout << "ERROR: mismatched parens: " << buffer << "\n";
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

        j++;

    }

    return NULL;

}

KolToken *parselist(string &expr, unsigned *start) {
    return NULL; // TODO
}

KolToken *parseexpr(string &expr, unsigned *start) {

    #if DEBUG >= 1
    cout << "parseexpr(" << expr << ")\n";
    #endif

    unsigned j = *start;
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

        #if DEBUG >= 1
        if (tokens.size() > 0) {
            cout << "previous token: " << tokens.back()->getClassname() << ", ";
        }
        cout << "current char: " << c << "\n";
        #endif

        if (j+1 < expr.length()) {
            lookahead = expr[j+1];
        } else {
            lookahead = 0;
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

        // TODO find a more efficient way of doing this? Possibly a huge switch statement?
        for (vector<pair<string, KolOperator *>>::iterator it = operators->begin(); it != operators->end(); it++) {
            string kop = it->first;
            if (j+kop.length() > expr.length()) {
                continue;
            }
            if (expr.compare(j, kop.length(), kop) == 0) {
                #if DEBUG >= 1
                cout << "encountered operator: " << kop << "\n";
                #endif
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

        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || c == '_') {
            tokens.push_back(parsevar(expr, &j));
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
        } else {
            j++;
        }
    }

    *start = j+1;
    #if DEBUG >= 1
    cout << "num tokens: " << tokens.size() << "\n";
    #endif

    vector<KolToken *> next_tokens;

    for (set<KolOperator *>::iterator it = ops.begin(); it != ops.end(); it++) {

        next_tokens = vector<KolToken *>();
        KolOperator *kop = *it;
        KolObject *self, *callback, *result;
        int max_arg = 0;

        #if DEBUG >= 1
        cout << "processing op: " << kop->getClassname() << "\n";
        #endif

        vector<int> &args = kop->getArgs();
        vector<bool> &is_bind_vars = kop->getIsBindVars();
        for (unsigned k = 0; k < args.size(); k++) {
            if (args[k] > max_arg) {
                max_arg = args[k];
            }
        }

        for (unsigned j = 0; j < tokens.size(); j++) {
            KolToken *kt = tokens[j];

            #if DEBUG >= 1
            cout << "processing token: " << kt->getClassname() << "\n";
            #endif

            if (kt == kop) {
                if (kop->getSelf() == -1) {

                    self = (KolObject *)next_tokens.back();

                    if (self->getClassname() == "__unbound__") {
                        self = kolScopeLookup(((KolUnboundVariable *)self)->getVarname());
                    }

                    next_tokens.pop_back();
                    #if DEBUG >= 1
                    cout << "self is previous token: " << self->getClassname() << "." << kop->getDunder() << "\n";
                    #endif
                    callback = self->access(kop->getDunder());

                } else if (kop->getSelf() == 0) {
                    self = NULL;
                    callback = kolScopeLookupBuiltin(kop->getDunder());
                } else {

                    if (tokens.size() <= j + kop->getSelf()) {
                        cout << "ERROR: missing argument to operator: " << kt->getClassname() << "\n";
                        return NULL;
                    }
                    self = (KolObject *)tokens[j + kop->getSelf()];

                    if (self->getClassname() == "__unbound__") {
                        self = kolScopeLookup(((KolUnboundVariable *)self)->getVarname());
                    }

                    callback = self->access(kop->getDunder());

                }

                #if DEBUG >= 1
                cout << "callback: " << callback << "\n";
                #endif

                vector<KolObject *> arg_objs;
                KolObject *arg_obj;

                if (self != NULL) {
                    arg_objs = { self };
                }

                for (unsigned k = 0; k < args.size(); k++) {
                    #if DEBUG >= 1
                    cout << "processing arg: i: " << k << ", args[i]: " << args[k] << ", is_bind_vars[i]: " << is_bind_vars[k] << "\n";
                    #endif
                    if (args[k] == -1) {
                        arg_obj = (KolObject *)next_tokens.back();
                        if (is_bind_vars[k] && arg_obj->getClassname() == "__unbound__") {
                            arg_obj = kolScopeLookup(((KolUnboundVariable *)arg_obj)->getVarname());
                        }
                        arg_objs.push_back(arg_obj);
                        next_tokens.pop_back();
                    } else {
                        if (tokens.size() <= j + args[k]) {
                            cout << "ERROR: missing argument to operator: " << kt->getClassname() << "\n";
                            return NULL;
                        }
                        arg_obj = (KolObject *)tokens[j + args[k]];
                        if (is_bind_vars[k] && arg_obj->getClassname() == "__unbound__") {
                            arg_obj = kolScopeLookup(((KolUnboundVariable *)arg_obj)->getVarname());
                        }
                        arg_objs.push_back(arg_obj);
                    }
                    #if DEBUG >= 1
                    cout << "successfully processed arg " << k << "\n";
                    #endif
                }

                #if DEBUG >= 1
                cout << "args: ";
                for (unsigned l = 0; l < arg_objs.size(); l++) {

                    if (arg_objs[l]->getClassname() == "int") {
                        cout << "int(" << ((KolInt *)arg_objs[l])->getValue() << ")";
                    } else if (arg_objs[l]->getClassname() == "float") {
                        cout << "float(" << ((KolFloat *)arg_objs[l])->getValue() << ")";
                    } else if (arg_objs[l]->getClassname() == "str") {
                        cout << "str(" << ((KolString *)arg_objs[l])->getValue() << ")";
                    }
                    cout << ", ";
                }
                cout << "\n";
                #endif

                result = ((KolMethodWrapper *)callback)->call(arg_objs);
                next_tokens.push_back(result);

                j += max_arg;

            } else {
                next_tokens.push_back(kt);
            }

        }

        tokens = next_tokens;

    }

    if (tokens.size() > 1) {
        cout << "WARNING: parsing line resulted in more than one token.\n";
        for (unsigned i = 0; i < tokens.size(); i++) {
            cout << "\ttoken " << i << ": " << ((tokens[i] != NULL) ? tokens[i]->getClassname() : "NULL" ) << "\n";
        }
        return tokens[0];
    } else if (tokens.size() == 0) {
        #if DEBUG >= 1
        cout << "WARNING: parsed empty line.\n";
        #endif
        return NULL;
    }

    // all good
    return tokens[0];

}

int parseline(string &line, bool is_interactive_mode) {

    #if DEBUG >= 1
    cout << "parsing line: " << line << '\n';
    #endif
    vector<KolToken *> tokens;
    vector<KolObject *> args;
    unsigned i = 0;

    while (i < line.size()) {
        KolToken *t = parseexpr(line, &i);
        if (t != NULL) {
            tokens.push_back(t);
        }
    }

    #if DEBUG >= 1

    if (tokens.size() == 0) {
        cout << ">>> " << "None\n";
    } else {
        for (unsigned j = 0; j < tokens.size(); j++) {
            args = { (KolObject *)tokens[j] };
            KolMethodWrapper *callback = (KolMethodWrapper *)((KolObject *)tokens[j])->access("__str__");
            KolString *res = (KolString *)callback->call(args);
            cout << ">>> " << res->getValue() << '\n';
        }
    }

    #endif

    if (is_interactive_mode) {
        for (unsigned j = 0; j < tokens.size(); j++) {
            args = { (KolObject *)tokens[j] };
            KolMethodWrapper *callback = (KolMethodWrapper *)((KolObject *)tokens[j])->access("__str__");
            KolString *res = (KolString *)callback->call(args);
            cout << res->getValue() << '\n';
        }
    }

    return 0;

}

int parse(ifstream &source) {

    char c;
    int res;
    string buffer;
    string parens;

    unsigned line_number = 1;

    while (source) {
       c = source.get();
       switch (c) {
           case '\n':
               if (parens.length() > 0) {
                   buffer.push_back(' ');
               } else {
                   res = parseline(buffer, false);
                   if (res != 0) {
                       return res;
                   }
                   buffer.clear();
               }
               line_number++;
               continue;

           case ';':
               if (parens.length() > 0) {
                   cout << "ERROR: Mismatched parens on line " << line_number << "\n";
                   return 1;
               } else {
                   res = parseline(buffer, false);
                   if (res != 0) {
                       return res;
                   }
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
                   cout << "ERROR: Mismatched parens on line " << line_number << "\n";
                   return 1;
               }
               parens.pop_back();
               buffer.push_back(c);
               continue;

           case ']':
               if (parens.back() != ']') {
                   cout << "ERROR: Mismatched square brackets on line " << line_number << "\n";
                   return 1;
               }
               parens.pop_back();
               buffer.push_back(c);
               continue;

           case '}':
               if (parens.back() != '}') {
                   cout << "ERROR: Mismatched curley braces on line " << line_number << "\n";
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

    if (buffer.size() > 0) {
        res = parseline(buffer, false);
        if (res != 0) {
            return res;
        }
    }

    return 0;

}


int parseInteractive() {

    char c;
    int res;
    unsigned i;
    string buffer, parens, userline;

    unsigned line_number = 1;

    while (true) {
        
        if (buffer.length() == 0) {
            cout << ">>> ";
        } else {
            cout << "... ";
        }

        getline(cin, userline);
        if (cin.eof() == 1) {
            cout << "\n";
            return 0;
        }

        for (i = 0; i < userline.length(); i++) {

            c = userline[i];

            switch (c) {

               case ';':
                   if (parens.length() > 0) {
                       cout << "ERROR: Mismatched parens on line " << line_number << "\n";
                   } else {
                       res = parseline(buffer, true);
                       if (res != 0) {
                           cout << "ERROR: processing line " << line_number << "\n";
                       }
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
                       cout << "ERROR: Mismatched parens on line " << line_number << "\n";
                       parens.clear();
                       buffer.clear();
                   } else {
                       parens.pop_back();
                       buffer.push_back(c);
                   }
                   continue;

               case ']':
                   if (parens.back() != ']') {
                       cout << "ERROR: Mismatched square brackets on line " << line_number << "\n";
                       parens.clear();
                       buffer.clear();
                   } else {
                       parens.pop_back();
                       buffer.push_back(c);
                   }
                   continue;

               case '}':
                   if (parens.back() != '}') {
                       cout << "ERROR: Mismatched curley braces on line " << line_number << "\n";
                       parens.clear();
                       buffer.clear();
                   } else {
                       parens.pop_back();
                       buffer.push_back(c);
                   }
                   continue;

               default:
                   buffer.push_back(c);
                   continue;
            } // end switch

        } // end for

        if (parens.length() == 0) {
            parseline(buffer, true);
            buffer.clear();
        }

    } // end while

    if (buffer.size() > 0) {
        res = parseline(buffer, true);
        if (res != 0) {
            return res;
        }
    }

    return 0;

}
