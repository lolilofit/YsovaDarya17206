#include "Celculate.h"
#include "exeptions.h"
#include<conio.h>

void Calculator::read(istream& in) {
	string operation;

	while (!in.eof()) {
		getline(in, operation);
		parse(operation);
	}
}

void Calculator::parse(string operation) {
	list<string> arguments;
	string arg;

	for (auto cur = operation.begin(); cur != operation.end(); ++cur) {

		if (*cur == ' ') {
			if (arg != "")
				arguments.push_back(arg);
			arg.clear();
		}
		else
			arg += *cur;
	}
	if (arg != "")
		arguments.push_back(arg);

//	Create f;
	try {
		string name = *arguments.begin();
		arguments.remove(*(arguments.begin()));

		Operations *one = Factory::get_instance().factory_metod(name)->make();
		one->abstract_operation(arguments, stack); 

		delete[] one;

	}
	catch (MyExceptions &e) {
		cout << "cought an exception:" << e.what() << '\n';
    	_getch();
	}
}
