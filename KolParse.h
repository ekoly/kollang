#include <string>

#include "KolObj.h"


KolToken *parsevar(string &expr, int &start);
KolToken *parsestring(string &expr, int *start);
KolToken *parsenumber(string &expr, int *start);
KolToken *parseset(string &expr, int *start);
KolToken *parsetuple(string &expr, int *start);
KolToken *parselist(string &expr, int *start);
KolToken *parseexpr(string &expr, int *start);
int parseline(string &line);
int parse(ifstream &source);
