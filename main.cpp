#include <string>
#include <iostream>
#include <fstream>

#include "KolMain.h"
#include "KolParse.h"

using namespace std;


int main(int argc, char **argv) {

    int res;
    string filename;
    ifstream kolfile;

    if (!kolMainSetup()) {
        cout << "ERROR: setup was not successful. Exiting.\n";
        return 1;
    }

    if (argc == 1) {
        parseInteractive();
    } else {
        for (int i = 1; i < argc; i++) {
            filename = string(argv[i]);
            kolfile = ifstream(filename);
            res = parse(kolfile);
            if (res != 0) {
                cout << "ERROR: interpretting file: " << argv[i] << "\n";
            }
        }
    }

    return 0;

}
