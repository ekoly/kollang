#include "KolScopes.h"
#include "KolTuple.h"


KolUnboundTuple::KolUnboundTuple() : KolObject("unbound-tuple") {

}

vector<KolObject *> &KolUnboundTuple::getValues() {
    return this->values;
}

int KolUnboundTuple::addValue(KolObject *value) {
    this->values.push_back(value);
    return 0;
}

KolTuple::KolTuple() : KolObject("tuple") {

}

KolTuple::KolTuple(KolUnboundTuple &initializer) : KolObject("tuple") {

    this->values = vector<KolObject *>(initializer.getValues());

}

vector<KolObject *> &KolTuple::getValues() {
    return this->values;
}

bool kolTupleSetup() {

    #if DEBUG >= 2
    cout << "kolTupleSetup(): setting up tuple built-ins\n";
    #endif

    KolObject *protoTuple = new KolTuple(),
              *protoUnboundTuple = new KolUnboundTuple();
    if (protoTuple == NULL || protoUnboundTuple == NULL) {
        return false;
    }

    kolScopeInsertBuiltin(protoTuple->getClassname(), protoTuple);
    kolScopeInsertBuiltin(protoUnboundTuple->getClassname(), protoUnboundTuple);

    #if DEBUG >= 2
    cout << "kolTupleSetup(): finished setting up tuple built-ins\n";
    #endif

    return true;

}
