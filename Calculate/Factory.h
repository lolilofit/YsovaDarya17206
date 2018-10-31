#ifndef FACTORY_H
#define FACTORY_H

#include"OperationsCreate.h"

class Factory {
	map<string, Create*> op;
	Factory() = default;
	Factory(const Factory &a) = delete;
public:
	static Factory& get_instance();

	void init_cmd(string name, Create* operation);

	Create* factory_metod(string name);
    
	~Factory();
};

#endif 

