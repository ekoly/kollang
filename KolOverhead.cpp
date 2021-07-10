#include <vector>
#include <string>
#include <iostream>

#include "KolMain.h"
#include "KolObj.h"
#include "KolScopes.h"
#include "KolOverhead.h"

using namespace std;


// Primitive method definitions
// primitive string
KolObject *protoStr__str__callback(vector<KolObject *> args) {
    KolString *self = (KolString *)args[0];
    KolString *result = new KolString("\"" + self->getValue() + "\"");
    return result;
}

// primitive int
KolObject *protoInt__str__callback(vector<KolObject *> args) {
    KolInt *self = (KolInt *)args[0];
    KolString *result = new KolString(to_string(self->getValue()));
    return result;
}
KolObject *protoInt__add__callback(vector<KolObject *> args) {
    KolInt *self = (KolInt *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolInt *result = new KolInt(self->getValue() + ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(self->getValue() + ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}
KolObject *protoInt__sub__callback(vector<KolObject *> args) {
    KolInt *self = (KolInt *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolInt *result = new KolInt(self->getValue() - ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(self->getValue() - ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}
KolObject *protoInt__mul__callback(vector<KolObject *> args) {
    KolInt *self = (KolInt *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolInt *result = new KolInt(self->getValue() * ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(self->getValue() * ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}
KolObject *protoInt__div__callback(vector<KolObject *> args) {
    KolInt *self = (KolInt *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolInt *result = new KolInt(self->getValue() / ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(self->getValue() / ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}

// primitive float
KolObject *protoFloat__str__callback(vector<KolObject *> args) {
    KolFloat *self = (KolFloat *)args[0];
    KolString *result = new KolString(to_string(self->getValue()));
    return result;
}
KolObject *protoFloat__add__callback(vector<KolObject *> args) {
    KolFloat *self = (KolFloat *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolFloat *result = new KolFloat(self->getValue() + ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(self->getValue() + ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}
KolObject *protoFloat__sub__callback(vector<KolObject *> args) {
    KolFloat *self = (KolFloat *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolFloat *result = new KolFloat(self->getValue() - ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(self->getValue() - ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}
KolObject *protoFloat__mul__callback(vector<KolObject *> args) {
    KolFloat *self = (KolFloat *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolFloat *result = new KolFloat(self->getValue() * ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(self->getValue() * ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}
KolObject *protoFloat__div__callback(vector<KolObject *> args) {
    KolFloat *self = (KolFloat *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolFloat *result = new KolFloat(self->getValue() / ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(self->getValue() / ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}

// operators
KolOperator kopfor = KolOperator("__for__", 0, {1, 2, 3}),
            kopwhile = KolOperator("__while__", 0, {1,}),
            kopcontinue = KolOperator("__continue__", 0, {}),
            kopbreak = KolOperator("__break__", 0, {}),
            kopin = KolOperator("__contains__", 1, {-1}),
            kopif = KolOperator("__if__", 0, {1}),
            kopelif = KolOperator("__elif__", 0, {1}),
            kopelse = KolOperator("__else__", 0, {}),
            kopdef = KolOperator("__def__", 0, {1}),
            kopclass = KolOperator("__class__", 0, {1}),
            kopprint = KolOperator("__print__", 0, {1}),
            kopadd = KolOperator("__add__", -1, {1}, 5),
            kopsub = KolOperator("__sub__", -1, {1}, 4),
            kopfloordiv = KolOperator("__floordiv__", -1, {1}, 3),
            kopdiv = KolOperator("__div__", -1, {1}, 2),
            kopmul = KolOperator("__mul__", -1, {1}, 1),
            kopeq = KolOperator("__eq__", -1, {1}),
            kopneq = KolOperator("__neq__", -1, {1}),
            kopgeq = KolOperator("__geq__", -1, {1}),
            kopleq = KolOperator("__leq__", -1, {1}),
            koplt = KolOperator("__lt__", -1, {1}),
            kopgt = KolOperator("__gt__", -1, {1}),
            kopassign = KolOperator("__assign__", 0, {-1, 1}, 1000),
            kopiadd = KolOperator("__iadd__", -1, {1}),
            kopisub = KolOperator("__isub__", -1, {1}),
            kopimul = KolOperator("__imul__", -1, {1}),
            kopidiv = KolOperator("__idiv__", -1, {1}),
            kopifloordiv = KolOperator("__ifloordiv__", -1, {1});

const vector<pair<string, KolOperator *>> *operators = new vector<pair<string, KolOperator *>>({
    { "for", &kopfor },
    { "while", &kopwhile },
    { "continue", &kopcontinue },
    { "break", &kopbreak },
    { "in", &kopin },
    { "if", &kopif },
    { "elif", &kopelif },
    { "else", &kopelse },
    { "def", &kopdef },
    { "class", &kopclass },
    { "print", &kopprint },
    { "==", &kopeq },
    { "!=", &kopneq },
    { ">=", &kopgeq },
    { "<=", &kopleq },
    { "*=", &kopimul },
    { "/=", &kopidiv },
    { "//=", &kopifloordiv },
    { "+=", &kopiadd },
    { "-=", &kopisub },
    { "*", &kopmul },
    { "//", &kopfloordiv },
    { "/", &kopdiv },
    { "+", &kopadd },
    { "-", &kopsub },
    { "<", &koplt },
    { ">", &kopgt },
    { "=", &kopassign },
});

bool kolOverheadSetup() {

    #if DEBUG == 1
    cout << "setting proto primitives" << "\n";
    #endif

    KolObject *protoStr = new KolString(""),
              *protoInt = new KolInt(0),
              *protoFloat = new KolFloat(0.0);

    #if DEBUG == 1
    cout << "setting builtins" << "\n";
    #endif

    // string builtin functions
    KolFunction *protoStr__str__ = new KolFunction();
    protoStr__str__->call = protoStr__str__callback;
    protoStr->setMember("__str__", protoStr__str__);

    // int builtin functions
    KolFunction *protoInt__str__ = new KolFunction();
    protoInt__str__->call = protoInt__str__callback;
    protoInt->setMember("__str__", protoInt__str__);

    KolFunction *protoInt__mul__ = new KolFunction();
    protoInt__mul__->call = protoInt__mul__callback;
    protoInt->setMember("__mul__", protoInt__mul__);

    KolFunction *protoInt__div__ = new KolFunction();
    protoInt__div__->call = protoInt__div__callback;
    protoInt->setMember("__div__", protoInt__div__);

    KolFunction *protoInt__add__ = new KolFunction();
    protoInt__add__->call = protoInt__add__callback;
    protoInt->setMember("__add__", protoInt__add__);

    KolFunction *protoInt__sub__ = new KolFunction();
    protoInt__sub__->call = protoInt__sub__callback;
    protoInt->setMember("__sub__", protoInt__sub__);

    // float buitin functions
    KolFunction *protoFloat__str__ = new KolFunction();
    protoFloat__str__->call = protoFloat__str__callback;
    protoFloat->setMember("__str__", protoFloat__str__);

    KolFunction *protoFloat__mul__ = new KolFunction();
    protoFloat__mul__->call = protoFloat__mul__callback;
    protoFloat->setMember("__mul__", protoFloat__mul__);

    KolFunction *protoFloat__div__ = new KolFunction();
    protoFloat__div__->call = protoFloat__div__callback;
    protoFloat->setMember("__div__", protoFloat__div__);

    KolFunction *protoFloat__add__ = new KolFunction();
    protoFloat__add__->call = protoFloat__add__callback;
    protoFloat->setMember("__add__", protoFloat__add__);

    KolFunction *protoFloat__sub__ = new KolFunction();
    protoFloat__sub__->call = protoFloat__sub__callback;
    protoFloat->setMember("__sub__", protoFloat__sub__);


    kolScopeInsertBuiltin(protoStr->getClassname(), protoStr);
    kolScopeInsertBuiltin(protoInt->getClassname(), protoInt);
    kolScopeInsertBuiltin(protoFloat->getClassname(), protoFloat);

    kolScopeInsertBuiltin("for", NULL);
    kolScopeInsertBuiltin("while", NULL);
    kolScopeInsertBuiltin("break", NULL);
    kolScopeInsertBuiltin("continue", NULL);
    kolScopeInsertBuiltin("in", NULL);
    kolScopeInsertBuiltin("global", NULL);
    kolScopeInsertBuiltin("return", NULL);
    kolScopeInsertBuiltin("if", NULL);
    kolScopeInsertBuiltin("elif", NULL);
    kolScopeInsertBuiltin("else", NULL);
    kolScopeInsertBuiltin("def", NULL);
    kolScopeInsertBuiltin("class", NULL);
    kolScopeInsertBuiltin("print", NULL);

    return true;

}


vector<pair<string, KolOperator *>> *getKolOperators() {
    return operators;
}
