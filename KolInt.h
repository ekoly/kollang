#ifndef KOL_INT_H
#define KOL_INT_H

#include "KolObj.h"

class KolInt : public KolObject {
    private:
        int value;

    public:
        KolInt(int value);

        int getValue();
};

bool kolIntSetup();

#endif
