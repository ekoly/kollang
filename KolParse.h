#ifndef KOL_PARSE_H
#define KOL_PARSE_H

#include <string>

#include "KolObj.h"


KolToken *parsevar(string &expr, unsigned *start);
KolToken *parsestring(string &expr, unsigned *start);
KolToken *parsenumber(string &expr, unsigned *start);
KolToken *parseset(string &expr, unsigned *start);
KolToken *parsetuple(string &expr, unsigned *start);
KolToken *parselist(string &expr, unsigned *start);
KolToken *parseexpr(string &expr, unsigned *start);
int parseline(string &line, bool is_interactive_mode);
int parseInteractive();
int parse(ifstream &source);

#endif
