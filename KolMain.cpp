#include <iostream>

#include "KolMain.h"
#include "KolObj.h"
#include "KolScopes.h"
#include "KolOverhead.h"
#include "KolInt.h"
#include "KolFloat.h"
#include "KolString.h"
#include "KolTuple.h"

using namespace std;


bool kolMainSetup() {

    bool res;
    res = kolScopeSetup();
    if (!res) {
        cout << "kolMainSetup(): Error setting up scopes, exiting.\n";
        return false;
    }

    res = kolOverheadSetup();
    if (!res) {
        cout << "kolOverheadSetup(): Error setting up overhead, exiting.\n";
        return false;
    }

    res = kolIntSetup();
    if (!res) {
        cout << "kolIntSetup(): Error setting up overhead, exiting.\n";
        return false;
    }

    res = kolFloatSetup();
    if (!res) {
        cout << "kolFloatSetup(): Error setting up overhead, exiting.\n";
        return false;
    }

    res = kolStringSetup();
    if (!res) {
        cout << "kolStringSetup(): Error setting up overhead, exiting.\n";
        return false;
    }

    res = kolTupleSetup();
    if (!res) {
        cout << "kolTupleSetup(): Error setting up overhead, exiting.\n";
        return false;
    }

    return true;

}
