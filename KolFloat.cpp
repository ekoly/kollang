#include <iostream>
#include <cmath>
#include <cstdlib>

#include "KolMain.h"
#include "KolScopes.h"
#include "KolInt.h"
#include "KolString.h"
#include "KolFloat.h"

using namespace std;


// class methods
KolFloat::KolFloat(double value) : KolObject("float") {
    this->value = value;
}

double KolFloat::getValue() {
    return this->value;
}

// accessible methods
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
        #if DEBUG >= 2
        cout << "protoFloat__pow__callback(" << to_string(self->getValue()) << ", " << to_string(((KolInt *)other)->getValue()) << ")\n";
        #endif
        KolFloat *result = new KolFloat(pow(self->getValue(), ((KolInt *)other)->getValue()));
        return result;
    } else if (other->getClassname() == "float") {
        #if DEBUG >= 2
        cout << "protoFloat__pow__callback(" << to_string(self->getValue()) << ", " << to_string(((KolFloat *)other)->getValue()) << ")\n";
        #endif
        KolFloat *result = new KolFloat(pow(self->getValue(), ((KolFloat *)other)->getValue()));
        return result;
    }

    return NULL;

}

bool kolFloatSetup() {

    #if DEBUG >= 2
    cout << "kolFloatSetup(): setting up float built-ins\n";
    #endif

    KolObject *protoFloat = new KolFloat(0.0);
    if (protoFloat == NULL) return false;

    // float buitin functions
    KolMethodWrapper *protoFloat__str__ = new KolMethodWrapper();
    if (protoFloat__str__ == NULL) return false;
    protoFloat__str__->call = protoFloat__str__callback;
    protoFloat->setMember("__str__", protoFloat__str__);

    KolMethodWrapper *protoFloat__mul__ = new KolMethodWrapper();
    if (protoFloat__mul__ == NULL) return false;
    protoFloat__mul__->call = protoFloat__mul__callback;
    protoFloat->setMember("__mul__", protoFloat__mul__);

    KolMethodWrapper *protoFloat__div__ = new KolMethodWrapper();
    if (protoFloat__div__ == NULL) return false;
    protoFloat__div__->call = protoFloat__div__callback;
    protoFloat->setMember("__div__", protoFloat__div__);

    KolMethodWrapper *protoFloat__floordiv__ = new KolMethodWrapper();
    if (protoFloat__floordiv__ == NULL) return false;
    protoFloat__floordiv__->call = protoFloat__floordiv__callback;
    protoFloat->setMember("__floordiv__", protoFloat__floordiv__);

    KolMethodWrapper *protoFloat__pow__ = new KolMethodWrapper();
    if (protoFloat__pow__ == NULL) return false;
    protoFloat__pow__->call = protoFloat__pow__callback;
    protoFloat->setMember("__pow__", protoFloat__pow__);

    KolMethodWrapper *protoFloat__add__ = new KolMethodWrapper();
    if (protoFloat__add__ == NULL) return false;
    protoFloat__add__->call = protoFloat__add__callback;
    protoFloat->setMember("__add__", protoFloat__add__);

    KolMethodWrapper *protoFloat__sub__ = new KolMethodWrapper();
    if (protoFloat__sub__ == NULL) return false;
    protoFloat__sub__->call = protoFloat__sub__callback;
    protoFloat->setMember("__sub__", protoFloat__sub__);

    kolScopeInsertBuiltin(protoFloat->getClassname(), protoFloat);

    #if DEBUG >= 2
    cout << "kolFloatSetup(): finished setting up float built-ins\n";
    #endif

    return true;

}
