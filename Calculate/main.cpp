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


int main(int argc, const char *argv[]) {
	ifstream in;
	Calculator my_calculator;

	if (argc == 2) {
		in.open(argv[1]);
		my_calculator.read_file(in);
	}
	else
		my_calculator.read_console();

	return 0;
}