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

KolOperator::KolOperator(string dunder, int self, vector<int> args) {
    this->dunder = dunder;
    this->self = self;
    this->args = args;
    this->precedence = 999;
}

KolOperator::KolOperator(string dunder, int self, vector<int> args, int precedence) {
    this->dunder = dunder;
    this->self = self;
    this->args = args;
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

KolNone::KolNone() : KolObject("NoneType") {

}

KolFunction::KolFunction() : KolObject("function") {

}

KolString::KolString(string value) : KolObject("str") {
    this->value = value;
}

string KolString::getValue() {
    return this->value;
}

KolFloat::KolFloat(double value) : KolObject("float") {
    this->value = value;
}

double KolFloat::getValue() {
    return this->value;
}

KolInt::KolInt(int value) : KolObject("int") {
    this->value = value;
}

int KolInt::getValue() {
    return this->value;
}
