#ifndef OPERATIONSCREATE_H
#define OPERATIONSCREATE_H

#include<iostream>
#include<list>
#include "Context.h"
#include "exeptions.h"
#include"OneOperation.h"

using namespace std;

class Base : public Operations {
public:
	void abstract_operation(list<string> arguments, Context &stack) override;
};

class Create {

public:
	virtual Operations* make() { return (new Base()); };
};


#endif