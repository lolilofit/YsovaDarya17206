#ifndef INIT_H
#define INIT_H

#include "Create.h"
#include "Factory.h"


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

 void init() {
	Factory::get_instance().init_cmd("PUSH", &_push);
	Factory::get_instance().init_cmd("POP", &_pop);
	Factory::get_instance().init_cmd("+", &_plus);
	Factory::get_instance().init_cmd("MINUS", &_minus);
	Factory::get_instance().init_cmd("/", &_divide);
	Factory::get_instance().init_cmd("*", &_mult);
	Factory::get_instance().init_cmd("SQRT", &_sqrt);
	Factory::get_instance().init_cmd("PRINT", &_print);
	Factory::get_instance().init_cmd("DEFINE", &_def);
	Factory::get_instance().init_cmd("#", &_comment);
	return;
}


#endif 
