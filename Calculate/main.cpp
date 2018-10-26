#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<list>
#include<map>
#include<vector>
#include "Context.h"
#include "Operations.h"
#include "Create.h"
#include "Celculate.h"
#include "exeptions.h"

using namespace std;

int OpenIn(const string InputFile, ifstream &in) {

	in.open(InputFile);
	if (!in.is_open()) {
		cerr << "no such file";
		return 1;
	}
	return 0;
}

int main(int argc, const char *argv[]) {
	ifstream in;
	Calculator my_calculator;
    
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

	Factory::get_instance()->init_cmd("PUSH", &_push);
	Factory::get_instance()->init_cmd("POP", &_pop);
	Factory::get_instance()->init_cmd("+", &_plus);
	Factory::get_instance()->init_cmd("MINUS", &_minus);
	Factory::get_instance()->init_cmd("/", &_divide);
	Factory::get_instance()->init_cmd("*", &_mult);
	Factory::get_instance()->init_cmd("SQRT", &_sqrt);
	Factory::get_instance()->init_cmd("PRINT", &_print);
	Factory::get_instance()->init_cmd("DEFINE", &_def);
	Factory::get_instance()->init_cmd("#", &_comment);

	if (argc == 2) {
		if (OpenIn(argv[1], in))
			return 0;
		my_calculator.read_file(in);
	}
	else
		my_calculator.read_console();

	return 0;
}