#include <map>
#include <vector>
#include <string>

#include "KolMain.h"
#include "KolObj.h"
#include "KolScopes.h"

using namespace std;


string KolToken::getClassname() {
    return "Undefined Token";
}

KolOperator::KolOperator(string dunder, int self, vector<int> args, vector<bool> is_bind_vars) {
    this->dunder = dunder;
    this->self = self;
    this->args = args;
    this->is_bind_vars = is_bind_vars;
    this->precedence = 999;
}

KolOperator::KolOperator(string dunder, int self, vector<int> args, vector<bool> is_bind_vars, int precedence) {
    this->dunder = dunder;
    this->self = self;
    this->args = args;
    this->is_bind_vars = is_bind_vars;
    this->precedence = precedence;
}

int KolOperator::getPrecedence() {
    return this->precedence;
}

string KolOperator::getDunder() {
    return this->dunder;
}

int KolOperator::getSelf() {
    return this->self;
}

vector<int> &KolOperator::getArgs() {
    return this->args;
}

vector<bool> &KolOperator::getIsBindVars() {
    return this->is_bind_vars;
}

string KolOperator::getClassname() {
    return this->dunder;
}

KolObject::KolObject() {
    this->members = new unordered_map<string, KolObject *>();
}

KolObject::KolObject(string classname) {
    this->classname = classname;
    KolObject *prototype = ((KolObject *)kolScopeLookup(classname));
    if (prototype == NULL) {
        kolScopeInsert(classname, this);
        this->members = new unordered_map<string, KolObject *>();
    } else {
        this->members = prototype->getMembersMap();
    }
}

KolObject *KolObject::access(string member) {

    auto it = this->members->find(member);
    if (it == this->members->end()) {
        return NULL;
    } else {
        return it->second;
    }

}

void KolObject::setMember(string key, KolObject *obj) {

    if (members->find(key) != members->end()) {
        members->erase(key);
    }

    members->insert({key, obj});

}

unordered_map<string, KolObject *> *KolObject::getMembersMap() {
    return this->members;
}

string KolObject::getClassname() {
    return this->classname;
}

KolUnboundVariable::KolUnboundVariable(string varname) : KolObject("__unbound__") {
    this->varname = varname;
}

string KolUnboundVariable::getVarname() {
    return this->varname;
}

KolNone::KolNone() : KolObject("NoneType") {

}

KolMethodWrapper::KolMethodWrapper() : KolObject("method-wrapper") {

}
