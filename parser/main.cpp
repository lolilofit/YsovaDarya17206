#include<iostream>
#include<tuple>
#include<fstream>
#include"pars.h"
#include"temp.h"


int main() {
	
	std::ifstream in;
	//std::ifstream in;
	in.open("in.csv");
	//const char ch = ' ';
	CSVParser<double, std::string> _parser(in, ',', 0);
	for (auto ptr = _parser.begin(); ptr != (_parser.end()); ++ptr) 
		std::cout << *ptr<<std::endl;
	return 0;
}