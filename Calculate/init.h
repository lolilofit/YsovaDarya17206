#ifndef INIT_H
#define INIT_H
#include "Create.h"

CreatePush _push;
CreatePop _pop;
CreatePlus _plus;
CreateMinus _minus;
CreateDivide _divide;
CreateMultiply _mult;
CreateSqrt _sqrt;
CreatePrint _print;
CreateDefine _def;
CreateComment _comment;

const map<string, Create*> Create::operations = { { "PUSH", &_push },
{ "POP", &_pop },
{ "+", &_plus },
{ "-", &_minus },
{ "/", &_divide },
{ "*", &_mult },
{ "SQRT", &_sqrt },
{ "PRINT", &_print },
{ "DEFINE", &_def },
{ "#", &_comment } };

#endif