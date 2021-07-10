#include <vector>
#include <unordered_map>
#include <string>

#include "KolObj.h"

bool kolScopeSetup();
KolObject *kolScopeLookup(string key);
bool kolScopeInsertBuiltin(string key, KolObject *val);
bool kolScopeInsertGlobal(string key, KolObject *val);
bool kolScopeInsert(string key, KolObject *val);
