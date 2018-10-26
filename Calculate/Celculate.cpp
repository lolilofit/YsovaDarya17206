#include "Celculate.h"
#include "exeptions.h"
#include<conio.h>

void Calculator::read_file(ifstream &in) {
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
		Operations* one = Factory::get_instance()->factory_metod(arguments)->make();
		one->abstract_operation(arguments, stack); 

//		(f.factory_metod(arguments, stack))->abstract_operation(arguments, stack);
	}
	catch (MyExceptions &e) {
		cout << "cought an exception:" << e.what() << '\n';
    	_getch();
	}
}

void Calculator::read_console() {
	string operation;
	while (1) {
		getline(cin, operation);
		parse(operation);
	}
}