#ifndef KOL_STRING_H
#define KOL_STRING_H

#include <string>

#include "KolObj.h"

using namespace std;

class KolString : public KolObject {

    private:
        string value;

    public:
        KolString(string value);

        string getValue();
};

bool kolStringSetup();

#endif
