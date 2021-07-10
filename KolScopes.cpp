#include <vector>
#include <unordered_map>
#include <iostream>

#include "KolMain.h"
#include "KolScopes.h"

using namespace std;


vector<unordered_map<string, KolObject *> *> kolScopes;

bool kolScopeSetup() {

    if (kolScopes.size() >= 2) {
        cout << "kolScopeSetup(): WARNING: kolScopes is already set up.\n";
    }

    kolScopes = vector<unordered_map<string, KolObject *> *>();

    unordered_map<string, KolObject *> *builtin = new unordered_map<string, KolObject *>(),
        *global = new unordered_map<string, KolObject *>();

    if (builtin == NULL || global == NULL) {
        return false;
    }

    kolScopes.push_back(builtin);
    kolScopes.push_back(global);

    return true;

}

KolObject *kolScopeLookupBuiltin(string key) {

    #if DEBUG == 1
    cout << "BUILTIN lookup: kolScopeLookupBuiltin(" << key << ")\n";
    if (kolScopes.size() < 2) {
        cout << "ERROR: scopes not set up!\n";
        return NULL;
    }
    #endif

    auto r = kolScopes[0]->find(key);
    if (r != kolScopes[0]->end()) {
        return r->second;
    }

    #if DEBUG == 1
    cout << "WARNING: no builtin found for key: " << key << "\n";
    #endif

    return NULL;
}

KolObject *kolScopeLookup(string key) {

    #if DEBUG == 1
    cout << "LOCAL lookup: kolScopeLookup(" << key << ")\n";
    if (kolScopes.size() < 2) {
        cout << "ERROR: scopes not set up!\n";
        return NULL;
    }
    #endif

    for (int j = kolScopes.size()-1; j >= 0; j--) {
        auto r = kolScopes[j]->find(key);
        if (r != kolScopes[j]->end()) {
            return r->second;
        }
    }

    #if DEBUG == 1
    cout << "WARNING: no variable found for key: " << key << "\n";
    #endif

    return NULL;
}

bool kolScopeInsertBuiltin(string key, KolObject *val) {

    #if DEBUG == 1
    cout << "BUILTIN insert: kolScopeInsertBuiltin(" << key << ", <" << ((val != NULL) ? val->getClassname() : "NULL") << ">)\n";
    if (kolScopes.size() < 2) {
        cout << "ERROR: scopes not set up!\n";
        return false;
    }
    #endif

    unordered_map<string, KolObject *> *builtin = kolScopes[0];

    builtin->insert({key, val});

    return true;

}

bool kolScopeInsertGlobal(string key, KolObject *val) {

    #if DEBUG == 1
    cout << "GLOBAL insert: kolScopeInsertGlobal(" << key << ", <" << ((val != NULL) ? val->getClassname() : "NULL") << ">)\n";
    if (kolScopes.size() < 2) {
        cout << "ERROR: scopes not set up!\n";
        return false;
    }
    #endif

    unordered_map<string, KolObject *> *global = kolScopes[1],
        *builtin = kolScopes[0];

    if (builtin->find(key) != builtin->end()) {
        cout << "kolScopeInsertGlobal(): ERROR: cannot override builtins: " << key << "\n";
        return false;
    }

    global->insert({key, val});

    return true;

}

bool kolScopeInsert(string key, KolObject *val) {

    #if DEBUG == 1
    cout << "LOCAL insert: kolScopeInsert(" << key << ", <" << ((val != NULL) ? val->getClassname() : "NULL") << ">)\n";
    if (kolScopes.size() < 2) {
        cout << "ERROR: scopes not set up!\n";
        return false;
    }
    #endif

    unordered_map<string, KolObject *> *kolScope = kolScopes.back(),
        *builtin = kolScopes[0];

    if (builtin->find(key) != builtin->end()) {
        cout << "kolScopeInsert(): ERROR: cannot override builtins: " << key << "\n";
        return false;
    }

    kolScope->insert({key, val});

    return true;

}
