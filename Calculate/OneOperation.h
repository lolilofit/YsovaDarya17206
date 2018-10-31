#ifndef ONEOPERATION_H
#define ONEOPERATION_H

#include<iostream>
#include<list>
#include "Context.h"
#include "exeptions.h"

using namespace std;

bool is_number(string val);

class Operations {
	
public:
	virtual void abstract_operation(list<string> arguments, Context &stack) {};
};

#endif // !ONEOPERATION_H
