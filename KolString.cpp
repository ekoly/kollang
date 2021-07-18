#include <iostream>

#include "KolMain.h"
#include "KolScopes.h"
#include "KolObj.h"
#include "KolString.h"

using namespace std;


// class methods
KolString::KolString(string value) : KolObject("str") {
    this->value = value;
}

string KolString::getValue() {
    return this->value;
}

// accessible methods
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

bool kolStringSetup() {

    #if DEBUG >= 2
    cout << "kolStringSetup(): setting up str built-ins\n";
    #endif

    KolObject *protoStr = new KolString("");
    if (protoStr == NULL) return false;

    KolMethodWrapper *protoStr__str__ = new KolMethodWrapper();
    if (protoStr__str__ == NULL) return false;
    protoStr__str__->call = protoStr__str__callback;
    protoStr->setMember("__str__", protoStr__str__);

    KolMethodWrapper *protoStr__add__ = new KolMethodWrapper();
    if (protoStr__add__ == NULL) return false;
    protoStr__add__->call = protoStr__add__callback;
    protoStr->setMember("__add__", protoStr__add__);

    kolScopeInsertBuiltin(protoStr->getClassname(), protoStr);

    #if DEBUG >= 2
    cout << "kolStringSetup(): finished setting up str built-ins\n";
    #endif

    return true;

}
