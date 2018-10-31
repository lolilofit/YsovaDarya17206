#ifndef CALCULATE_H
#define CALCULATE_H
#include "Context.h"
#include "Operations.h"
#include "Create.h"
#include "Factory.h"
#include "Context.h"
#include "exeptions.h"

class Calculator {

	Context stack;
	void parse(string arg);
public:

	void read(istream& in);

};



#endif 