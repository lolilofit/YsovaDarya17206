#ifndef FACTORY_H
#define FACTORY_H
#include "Create.h"


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

#endif // !FACTORY_H

