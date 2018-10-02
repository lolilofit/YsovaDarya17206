#include<iostream>
#include<string>
#include<fstream>
#include"Words.h"

using namespace std;



void OpenIn(const string InputFile, ifstream &in) {
	
	in.open(InputFile);
	if (!in.is_open()) 
		cerr << "no such file";
}

void OpenOut(const string OutFile, ofstream &out) {
	out.open(OutFile);
	if (!out.is_open()) 
		cerr << "no such file";
		
}

int main(int argc, const char *argv[]) {

	ifstream in;
	ofstream out;
	
	if (argc == 3) {
		OpenIn(argv[1], in);
		OpenOut(argv[2], out);
		if (!in.is_open() || !out.is_open())
			return 0;
	}
	else {
		cout << "wrong number of arguments";
		return 0;
	}
	
	words st;	
    st.CountWords(in, out);
	in.close();
	out.close();
	return 0;
}
