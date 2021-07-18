#ifndef KOL_TUPLE_H
#define KOL_TUPLE_H

#include <vector>

#include "KolObj.h"

using namespace std;


class KolUnboundTuple : public KolObject {
    private:
        vector<KolObject *> values;

    public:
        KolUnboundTuple();

        vector<KolObject *> &getValues();
        int addValue(KolObject *value);
};

class KolTuple : public KolObject {
    private:
        vector<KolObject *> values;

    public:
        KolTuple();
        KolTuple(KolUnboundTuple &initializer);

        vector<KolObject *> &getValues();
};

bool kolTupleSetup();

#endif
