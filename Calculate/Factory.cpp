#include "Factory.h"

Factory& Factory::get_instance() {
	static Factory _factory;
	return _factory;
}

void Factory::init_cmd(string name, Create* operation) {
	op[name] = operation;
}

Create* Factory::factory_metod(string name) {
	if (op.count(name) == 0)
		throw Is_operation();
	return op.at(name);
}

Factory::~Factory() {
	for (auto cur : op) {
		delete(cur.second);
		cur.second = nullptr;
	}
}