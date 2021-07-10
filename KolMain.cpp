#include <iostream>

#include "KolMain.h"
#include "KolObj.h"
#include "KolScopes.h"
#include "KolOverhead.h"

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

    return true;

}
