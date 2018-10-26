#ifndef FACTORY_H
#define FACTORY_H

#include<iostream>
#include<list>
#include "Context.h"
#include "exeptions.h"

using namespace std;

class Operations {
public:
	virtual void abstract_operation(list<string> arguments, Context &stack) {};
	bool is_number(string val);
	virtual void catch_ecxeption(list<string> arguments, Context &stack) {};
};

class Base : public Operations {
public:
	void abstract_operation(list<string> arguments, Context &stack) override;
};

class Create {
public:
	virtual Operations* make() { return (new Base()); };
};

class Factory {
	map<string, Create*> op;
	Factory() = default;
	Factory(const Factory &a) = delete;
public:
	static Factory* get_instance();

	void init_cmd(string name, Create* operation);

	/*
	Create* read_cmd(string name) {
		return op[name];
	}
	*/
	Create* factory_metod(list<string> &arguments);
};

#endif 

