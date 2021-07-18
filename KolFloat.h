#ifndef KOL_FLOAT_H
#define KOL_FLOAT_H

#include "KolObj.h"

class KolFloat : public KolObject {
    private:
        double value;

    public:
        KolFloat(double value);

        double getValue();
};

bool kolFloatSetup();

#endif
