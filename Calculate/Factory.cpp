#include "Factory.h"

Factory* Factory::get_instance() {
	static Factory _factory;
	return &_factory;
}

void Factory::init_cmd(string name, Create* operation) {
	op[name] = operation;
}

Create* Factory::factory_metod(list<string> &arguments) {
	string name = *arguments.begin();
	arguments.remove(*(arguments.begin()));
	return op.at(name);
}