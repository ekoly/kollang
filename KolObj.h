#ifndef KOL_OBJ_H
#define KOL_OBJ_H

#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;


class KolToken {

    public:

        virtual string getClassname();

};


class KolOperator : public KolToken {

    private:
        string dunder;
        int self, precedence;
        vector<int> args;
        vector<bool> is_bind_vars;

    public:

        KolOperator(string dunder, int self, vector<int> args, vector<bool> is_bind_vars);
        KolOperator(string dunder, int self, vector<int> args, vector<bool> is_bind_vars, int precedence);

        int getPrecedence();

        string getDunder();
        int getSelf();
        vector<int> &getArgs();
        vector<bool> &getIsBindVars();
        string getClassname();
};

class KolObject : public KolToken {

    protected:

        unordered_map<string, KolObject *> *members;
        string classname;

    public:

        KolObject();
        KolObject(string classname);

        KolObject *access(string member);
        void setMember(string key, KolObject *obj);
        unordered_map<string, KolObject *> *getMembersMap();
        string getClassname();

};


class KolUnboundVariable : public KolObject {

    protected:

        string varname;
        
    public:

        KolUnboundVariable(string varname);
        
        string getVarname();

};


class KolNone : public KolObject {

    public:
        
        KolNone();

};

class KolFunction : public KolObject {

    public:

        KolFunction();
        function<KolObject *(vector<KolObject *> &)> call;

};

class KolString : public KolObject {

    private:
        string value;

    public:
        KolString(string value);

        string getValue();
};

class KolFloat : public KolObject {
    private:
        double value;

    public:
        KolFloat(double value);

        double getValue();
};

class KolInt : public KolObject {
    private:
        int value;

    public:
        KolInt(int value);

        int getValue();
};

#endif
