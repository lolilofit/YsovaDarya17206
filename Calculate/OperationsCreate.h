#ifndef OPERATIONSCREATE_H
#define OPERATIONSCREATE_H

#include<iostream>
#include<list>
#include "Context.h"
#include "exeptions.h"
#include"OneOperation.h"

using namespace std;


class Create {

public:
	virtual Operations* make() = 0;
};


#endif