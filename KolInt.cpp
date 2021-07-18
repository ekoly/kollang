#include <cmath>
#include <cstdlib>
#include <iostream>

#include "KolMain.h"
#include "KolScopes.h"
#include "KolInt.h"
#include "KolFloat.h"
#include "KolString.h"

using namespace std;


// class methods
KolInt::KolInt(int value) : KolObject("int") {
    this->value = value;
}

int KolInt::getValue() {
    return this->value;
}

// accessible methods
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

bool kolIntSetup() {

    #if DEBUG >= 2
    cout << "kolIntSetup(): setting up int built-ins\n";
    #endif

    KolObject *protoInt = new KolInt(0);
    if (protoInt == NULL) return false;

    KolMethodWrapper *protoInt__str__ = new KolMethodWrapper();
    if (protoInt__str__ == NULL) return false;
    protoInt__str__->call = protoInt__str__callback;
    protoInt->setMember("__str__", protoInt__str__);

    KolMethodWrapper *protoInt__mul__ = new KolMethodWrapper();
    if (protoInt__mul__ == NULL) return false;
    protoInt__mul__->call = protoInt__mul__callback;
    protoInt->setMember("__mul__", protoInt__mul__);

    KolMethodWrapper *protoInt__div__ = new KolMethodWrapper();
    if (protoInt__div__ == NULL) return false;
    protoInt__div__->call = protoInt__div__callback;
    protoInt->setMember("__div__", protoInt__div__);

    KolMethodWrapper *protoInt__floordiv__ = new KolMethodWrapper();
    if (protoInt__floordiv__ == NULL) return false;
    protoInt__floordiv__->call = protoInt__floordiv__callback;
    protoInt->setMember("__floordiv__", protoInt__floordiv__);

    KolMethodWrapper *protoInt__pow__ = new KolMethodWrapper();
    if (protoInt__pow__ == NULL) return false;
    protoInt__pow__->call = protoInt__pow__callback;
    protoInt->setMember("__pow__", protoInt__pow__);

    KolMethodWrapper *protoInt__add__ = new KolMethodWrapper();
    if (protoInt__add__ == NULL) return false;
    protoInt__add__->call = protoInt__add__callback;
    protoInt->setMember("__add__", protoInt__add__);

    KolMethodWrapper *protoInt__sub__ = new KolMethodWrapper();
    if (protoInt__sub__ == NULL) return false;
    protoInt__sub__->call = protoInt__sub__callback;
    protoInt->setMember("__sub__", protoInt__sub__);

    kolScopeInsertBuiltin(protoInt->getClassname(), protoInt);

    #if DEBUG >= 2
    cout << "kolIntSetup(): finished setting up int built-ins\n";
    #endif

    return true;

}
