#include <string>
#include <iostream>
#include <fstream>

#include "KolMain.h"
#include "KolObj.h"
#include "KolScopes.h"
#include "KolOverhead.h"
#include "KolParse.h"

using namespace std;


int main(int argc, char **argv) {

    string filename;

    if (!kolMainSetup()) {
        cout << "ERROR: setup was not successful. Exiting.\n";
        return 1;
    }

    if (argc == 2) {
        string filename(argv[1]);
        ifstream kolfile(filename);
        return parse(kolfile);
    }

    return 0;

}
