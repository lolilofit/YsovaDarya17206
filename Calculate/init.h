#ifndef INIT_H
#define INIT_H

#include "Create.h"
#include "Factory.h"


 void init() {


	 CreatePush* _push = new CreatePush();
	 CreatePop* _pop = new CreatePop();
	 CreatePlus* _plus = new CreatePlus();
	 CreateMinus* _minus = new CreateMinus();
	 CreateDivide* _divide = new CreateDivide();
	 CreateMultiply* _mult = new CreateMultiply();
	 CreateSqrt* _sqrt = new CreateSqrt();
	 CreatePrint* _print = new CreatePrint();
	 CreateDefine* _def = new CreateDefine();
	 CreateComment* _comment = new CreateComment();
	Factory::get_instance().init_cmd("PUSH", _push);
	Factory::get_instance().init_cmd("POP", _pop);
	Factory::get_instance().init_cmd("+", _plus);
	Factory::get_instance().init_cmd("MINUS", _minus);
	Factory::get_instance().init_cmd("/", _divide);
	Factory::get_instance().init_cmd("*", _mult);
	Factory::get_instance().init_cmd("SQRT", _sqrt);
	Factory::get_instance().init_cmd("PRINT", _print);
	Factory::get_instance().init_cmd("DEFINE", _def);
	Factory::get_instance().init_cmd("#", _comment);
	return;
}


#endif 
