#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<list>
#include<map>
#include<vector>
#include "Context.h"
#include "Operations.h"
#include "Create.h"
#include "Celculate.h"
#include "init.h"
#include "exeptions.h"

using namespace std;

int OpenIn(const string InputFile, ifstream &in) {

	in.open(InputFile);
	if (!in.is_open()) {
		cerr << "no such file";
		return 1;
	}
	return 0;
}

int main(int argc, const char *argv[]) {
	ifstream in;
	Calculator my_calculator;

	if (argc == 2) {
		if (OpenIn(argv[1], in))
			return 0;
		my_calculator.read_file(in);
	}
	else
		my_calculator.read_console();

	return 0;
}