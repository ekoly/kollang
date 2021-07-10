#ifndef KOL_SCOPES_H
#define KOL_SCOPES_H 

#include <string>

#include "KolObj.h"

bool kolScopeSetup();
KolObject *kolScopeLookupBuiltin(string key);
KolObject *kolScopeLookup(string key);
bool kolScopeInsertBuiltin(string key, KolObject *val);
bool kolScopeInsertGlobal(string key, KolObject *val);
bool kolScopeInsert(string key, KolObject *val);

#endif
