#ifndef CALCULATE_H
#define CALCULATE_H
#include "Context.h"
#include "Operations.h"
#include "Create.h"
#include "Factory.h"

class Calculator {

	Context stack;
	void parse(string arg);
public:

	void read_file(ifstream &in);
	void read_console();
};



#endif 