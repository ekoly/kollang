#include <vector>
#include <string>
#include <iostream>

#include "KolMain.h"
#include "KolObj.h"
#include "KolScopes.h"
#include "KolTuple.h"
#include "KolOverhead.h"

using namespace std;


// Primitive method definitions
KolObject *proto__assign__callback(vector<KolObject *> &args) {

    #if DEBUG >= 2
    cout << "proto__assign__callback()\n";
    #endif

    KolObject *self = args[0],
        *other = args[1];

    if (self->getClassname() != "__unbound__") {
        cerr << "ERROR: invalid left side of assign statement.\n";
    }

    if (!kolScopeInsert(((KolUnboundVariable *)self)->getVarname(), other)) {
        cerr << "ERROR: unable to set variable.\n";
    }

    return NULL;
}

KolObject *proto__comma__callback(vector<KolObject *> &args) {

    #if DEBUG >= 2
    cout << "proto__comma__callback()\n";
    #endif

    KolUnboundTuple *unbound_tuple;
    KolObject *other = args[1];

    if (args[0] != NULL && args[0]->getClassname() == "unbound-tuple") {
        unbound_tuple = (KolUnboundTuple *)args[0];
        #if DEBUG >= 2
        cout << "proto__comma__callback(): found existing unbound-tuple, with " << unbound_tuple->getValues().size() << " elements.\n";
        #endif
    } else {
        #if DEBUG >= 2
        cout << "proto__comma__callback(): found no existing unbound-tuple, creating new one\n";
        #endif
        unbound_tuple = new KolUnboundTuple();
    }

    unbound_tuple->addValue(other);

    return unbound_tuple;

}

// operators
KolOperator kopfor = KolOperator("__for__", 0, {1, 2, 3}, {false, true, true}),
            kopwhile = KolOperator("__while__", 0, {1}, {true}),
            kopcontinue = KolOperator("__continue__", 0, {}, {}),
            kopbreak = KolOperator("__break__", 0, {}, {}),
            kopin = KolOperator("__contains__", 1, {-1}, {true}),
            kopif = KolOperator("__if__", 0, {1}, {true}),
            kopelif = KolOperator("__elif__", 0, {1}, {true}),
            kopelse = KolOperator("__else__", 0, {}, {}),
            kopdef = KolOperator("__def__", 0, {1}, {false}),
            kopclass = KolOperator("__class__", 0, {1}, {false}),
            kopprint = KolOperator("__print__", 0, {1}, {true}),
            kopadd = KolOperator("__add__", -1, {1}, {true}, 5),
            kopsub = KolOperator("__sub__", -1, {1}, {true}, 4),
            kopfloordiv = KolOperator("__floordiv__", -1, {1}, {true}, 3),
            kopdiv = KolOperator("__div__", -1, {1}, {true}, 2),
            kopmul = KolOperator("__mul__", -1, {1}, {true}, 1),
            koppow = KolOperator("__pow__", -1, {1}, {true}, 0),
            kopeq = KolOperator("__eq__", -1, {1}, {true}),
            kopneq = KolOperator("__neq__", -1, {1}, {true}),
            kopgeq = KolOperator("__geq__", -1, {1}, {true}),
            kopleq = KolOperator("__leq__", -1, {1}, {true}),
            koplt = KolOperator("__lt__", -1, {1}, {true}),
            kopgt = KolOperator("__gt__", -1, {1}, {true}),
            kopassign = KolOperator("__assign__", 0, {-1, 1}, {false, true}, 1000),
            kopiadd = KolOperator("__iadd__", -1, {1}, {true}),
            kopisub = KolOperator("__isub__", -1, {1}, {true}),
            kopimul = KolOperator("__imul__", -1, {1}, {true}),
            kopidiv = KolOperator("__idiv__", -1, {1}, {true}),
            kopifloordiv = KolOperator("__ifloordiv__", -1, {1}, {true}),
            kopcomma = KolOperator("__comma__", 0, {-2, -1}, {false}, 500),
            kopdot = KolOperator("__dot__", -1, {1}, {false}, 0);

vector<pair<string, KolOperator *> > *operators = new vector<pair<string, KolOperator *> >({
    { "for", &kopfor },
    { "while", &kopwhile },
    { "continue", &kopcontinue },
    { "break", &kopbreak },
    { "in", &kopin },
    { "if", &kopif },
    { "elif", &kopelif },
    { "else", &kopelse },
    { "def", &kopdef },
    { "class", &kopclass },
    { "print", &kopprint },
    { "==", &kopeq },
    { "!=", &kopneq },
    { ">=", &kopgeq },
    { "<=", &kopleq },
    { "*=", &kopimul },
    { "//=", &kopifloordiv },
    { "/=", &kopidiv },
    { "+=", &kopiadd },
    { "-=", &kopisub },
    { "**", &koppow },
    { "*", &kopmul },
    { "//", &kopfloordiv },
    { "/", &kopdiv },
    { "+", &kopadd },
    { "-", &kopsub },
    { "<", &koplt },
    { ">", &kopgt },
    { "=", &kopassign },
    { ",", &kopcomma },
    { ".", &kopdot },
});

bool kolOverheadSetup() {

    #if DEBUG >= 2
    cout << "setting proto primitives" << "\n";
    #endif

    KolObject *protoNone = new KolNone();

    #if DEBUG >= 2
    cout << "####################\n";
    cout << "# setting builtins #\n";
    cout << "####################\n";
    #endif

    KolMethodWrapper *proto__assign__ = new KolMethodWrapper();
    proto__assign__->call = proto__assign__callback;

    KolMethodWrapper *proto__comma__ = new KolMethodWrapper();
    proto__comma__->call = proto__comma__callback;

    kolScopeInsertBuiltin("None", protoNone);
    kolScopeInsertBuiltin("NoneType", protoNone);
    kolScopeInsertBuiltin("__unbound__", protoNone);
    kolScopeInsertBuiltin("__assign__", proto__assign__);
    kolScopeInsertBuiltin("__comma__", proto__assign__);
    kolScopeInsertBuiltin("for", protoNone);
    kolScopeInsertBuiltin("while", protoNone);
    kolScopeInsertBuiltin("break", protoNone);
    kolScopeInsertBuiltin("continue", protoNone);
    kolScopeInsertBuiltin("in", protoNone);
    kolScopeInsertBuiltin("global", protoNone);
    kolScopeInsertBuiltin("globals", protoNone);
    kolScopeInsertBuiltin("locals", protoNone);
    kolScopeInsertBuiltin("return", protoNone);
    kolScopeInsertBuiltin("if", protoNone);
    kolScopeInsertBuiltin("elif", protoNone);
    kolScopeInsertBuiltin("else", protoNone);
    kolScopeInsertBuiltin("def", protoNone);
    kolScopeInsertBuiltin("class", protoNone);
    kolScopeInsertBuiltin("print", protoNone);
    kolScopeInsertBuiltin("del", protoNone);

    #if DEBUG >= 2
    cout << "#############################\n";
    cout << "# finished setting builtins #\n";
    cout << "#############################\n";
    #endif


    return true;

}


vector<pair<string, KolOperator *> > *getKolOperators() {
    return operators;
}
