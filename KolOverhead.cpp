#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "KolMain.h"
#include "KolObj.h"
#include "KolScopes.h"
#include "KolOverhead.h"

using namespace std;


KolNone none;

// Primitive method definitions
KolObject *proto__assign__callback(vector<KolObject *> &args) {

    #if DEBUG == 1
    cout << "proto__assign__callback()\n";
    #endif

    KolObject *self = args[0],
        *other = args[1];

    if (self->getClassname() != "__unbound__") {
        cout << "ERROR: invalid left side of assign statement.\n";
    }

    if (!kolScopeInsert(((KolUnboundVariable *)self)->getVarname(), other)) {
        cout << "ERROR: unable to set variable.\n";
    }

    return NULL;
}

// primitive string
KolObject *protoStr__str__callback(vector<KolObject *> &args) {
    KolString *self = (KolString *)args[0];
    KolString *result = new KolString("\"" + self->getValue() + "\"");
    return result;
}
KolObject *protoStr__add__callback(vector<KolObject *> &args) {
    KolString *self = (KolString *)args[0],
        *other = (KolString *)args[1];

    KolString *result = new KolString(self->getValue() + other->getValue());

    return result;
};

// primitive int
KolObject *protoInt__str__callback(vector<KolObject *> &args) {
    KolInt *self = (KolInt *)args[0];
    KolString *result = new KolString(to_string(self->getValue()));
    return result;
}
KolObject *protoInt__add__callback(vector<KolObject *> &args) {
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
KolObject *protoInt__sub__callback(vector<KolObject *> &args) {
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
KolObject *protoInt__mul__callback(vector<KolObject *> &args) {
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
KolObject *protoInt__div__callback(vector<KolObject *> &args) {
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
KolObject *protoInt__floordiv__callback(vector<KolObject *> &args) {
    KolInt *self = (KolInt *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolInt *result = new KolInt(self->getValue() / ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolInt *result = new KolInt(self->getValue() / ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}
KolObject *protoInt__pow__callback(vector<KolObject *> &args) {
    KolInt *self = (KolInt *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolInt *result = new KolInt(pow(self->getValue(), ((KolInt *)other)->getValue()));
        return result;
    } else if (other->getClassname() == "float") {
        KolFloat *result = new KolFloat(pow(self->getValue(), ((KolFloat *)other)->getValue()));
        return result;
    }

    return NULL;

}

// primitive float
KolObject *protoFloat__str__callback(vector<KolObject *> &args) {
    KolFloat *self = (KolFloat *)args[0];
    KolString *result = new KolString(to_string(self->getValue()));
    return result;
}
KolObject *protoFloat__add__callback(vector<KolObject *> &args) {
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
KolObject *protoFloat__sub__callback(vector<KolObject *> &args) {
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
KolObject *protoFloat__mul__callback(vector<KolObject *> &args) {
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
KolObject *protoFloat__div__callback(vector<KolObject *> &args) {
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
KolObject *protoFloat__floordiv__callback(vector<KolObject *> &args) {
    KolFloat *self = (KolFloat *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        KolInt *result = new KolInt(self->getValue() / ((KolInt *)other)->getValue());
        return result;
    } else if (other->getClassname() == "float") {
        KolInt *result = new KolInt(self->getValue() / ((KolFloat *)other)->getValue());
        return result;
    }

    return NULL;

}
KolObject *protoFloat__pow__callback(vector<KolObject *> &args) {

    KolFloat *self = (KolFloat *)args[0];
    KolObject *other = args[1];

    if (other->getClassname() == "int") {
        #if DEBUG == 1
        cout << "protoFloat__pow__callback(" << to_string(self->getValue()) << ", " << to_string(((KolInt *)other)->getValue()) << ")\n";
        #endif
        KolFloat *result = new KolFloat(pow(self->getValue(), ((KolInt *)other)->getValue()));
        return result;
    } else if (other->getClassname() == "float") {
        #if DEBUG == 1
        cout << "protoFloat__pow__callback(" << to_string(self->getValue()) << ", " << to_string(((KolFloat *)other)->getValue()) << ")\n";
        #endif
        KolFloat *result = new KolFloat(pow(self->getValue(), ((KolFloat *)other)->getValue()));
        return result;
    }

    return NULL;

}

// operators
KolOperator kopfor = KolOperator("__for__", 0, {1, 2, 3}, {false, true, true}),
            kopwhile = KolOperator("__while__", 0, {1}, {true}),
            kopcontinue = KolOperator("__continue__", 0, {}, {}),
            kopbreak = KolOperator("__break__", 0, {}, {}),
            kopin = KolOperator("__contains__", 1, {-1}, {true}),
            kopif = KolOperator("__if__", 0, {1}, {true}),
            kopelif = KolOperator("__elif__", 0, {1}, {true}),
            kopelse = KolOperator("__else__", 0, {}, {}),
            kopdef = KolOperator("__def__", 0, {1}, {false}),
            kopclass = KolOperator("__class__", 0, {1}, {false}),
            kopprint = KolOperator("__print__", 0, {1}, {true}),
            kopadd = KolOperator("__add__", -1, {1}, {true}, 5),
            kopsub = KolOperator("__sub__", -1, {1}, {true}, 4),
            kopfloordiv = KolOperator("__floordiv__", -1, {1}, {true}, 3),
            kopdiv = KolOperator("__div__", -1, {1}, {true}, 2),
            kopmul = KolOperator("__mul__", -1, {1}, {true}, 1),
            koppow = KolOperator("__pow__", -1, {1}, {true}, 0),
            kopeq = KolOperator("__eq__", -1, {1}, {true}),
            kopneq = KolOperator("__neq__", -1, {1}, {true}),
            kopgeq = KolOperator("__geq__", -1, {1}, {true}),
            kopleq = KolOperator("__leq__", -1, {1}, {true}),
            koplt = KolOperator("__lt__", -1, {1}, {true}),
            kopgt = KolOperator("__gt__", -1, {1}, {true}),
            kopassign = KolOperator("__assign__", 0, {-1, 1}, {false, true}, 1000),
            kopiadd = KolOperator("__iadd__", -1, {1}, {true}),
            kopisub = KolOperator("__isub__", -1, {1}, {true}),
            kopimul = KolOperator("__imul__", -1, {1}, {true}),
            kopidiv = KolOperator("__idiv__", -1, {1}, {true}),
            kopifloordiv = KolOperator("__ifloordiv__", -1, {1}, {true});

vector<pair<string, KolOperator *> > *operators = new vector<pair<string, KolOperator *> >({
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
    { "**", &koppow },
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
    cout << "####################\n";
    cout << "# setting builtins #\n";
    cout << "####################\n";
    #endif

    KolFunction *proto__assign__ = new KolFunction();
    proto__assign__->call = proto__assign__callback;

    // string builtin functions
    KolFunction *protoStr__str__ = new KolFunction();
    protoStr__str__->call = protoStr__str__callback;
    protoStr->setMember("__str__", protoStr__str__);

    KolFunction *protoStr__add__ = new KolFunction();
    protoStr__add__->call = protoStr__add__callback;
    protoStr->setMember("__add__", protoStr__add__);

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

    KolFunction *protoInt__floordiv__ = new KolFunction();
    protoInt__floordiv__->call = protoInt__floordiv__callback;
    protoInt->setMember("__floordiv__", protoInt__floordiv__);

    KolFunction *protoInt__pow__ = new KolFunction();
    protoInt__pow__->call = protoInt__pow__callback;
    protoInt->setMember("__pow__", protoInt__pow__);

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

    KolFunction *protoFloat__floordiv__ = new KolFunction();
    protoFloat__floordiv__->call = protoFloat__floordiv__callback;
    protoFloat->setMember("__floordiv__", protoFloat__floordiv__);

    KolFunction *protoFloat__pow__ = new KolFunction();
    protoFloat__pow__->call = protoFloat__pow__callback;
    protoFloat->setMember("__pow__", protoFloat__pow__);

    KolFunction *protoFloat__add__ = new KolFunction();
    protoFloat__add__->call = protoFloat__add__callback;
    protoFloat->setMember("__add__", protoFloat__add__);

    KolFunction *protoFloat__sub__ = new KolFunction();
    protoFloat__sub__->call = protoFloat__sub__callback;
    protoFloat->setMember("__sub__", protoFloat__sub__);


    kolScopeInsertBuiltin(protoStr->getClassname(), protoStr);
    kolScopeInsertBuiltin(protoInt->getClassname(), protoInt);
    kolScopeInsertBuiltin(protoFloat->getClassname(), protoFloat);

    kolScopeInsertBuiltin("None", &none);
    kolScopeInsertBuiltin("NoneType", &none);
    kolScopeInsertBuiltin("__unbound__", &none);
    kolScopeInsertBuiltin("__assign__", proto__assign__);
    kolScopeInsertBuiltin("for", &none);
    kolScopeInsertBuiltin("while", &none);
    kolScopeInsertBuiltin("break", &none);
    kolScopeInsertBuiltin("continue", &none);
    kolScopeInsertBuiltin("in", &none);
    kolScopeInsertBuiltin("global", &none);
    kolScopeInsertBuiltin("return", &none);
    kolScopeInsertBuiltin("if", &none);
    kolScopeInsertBuiltin("elif", &none);
    kolScopeInsertBuiltin("else", &none);
    kolScopeInsertBuiltin("def", &none);
    kolScopeInsertBuiltin("class", &none);
    kolScopeInsertBuiltin("print", &none);

    #if DEBUG == 1
    cout << "#############################\n";
    cout << "# finished setting builtins #\n";
    cout << "#############################\n";
    #endif


    return true;

}


vector<pair<string, KolOperator *> > *getKolOperators() {
    return operators;
}
