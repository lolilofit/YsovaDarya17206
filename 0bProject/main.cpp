#include<iostream>
#include<string>
#include<fstream>
#include"Words.h"

using namespace std;



int OpenIn(const string InputFile, ifstream &in) {
	
	in.open(InputFile);
	if (!in.is_open()) {
		cerr << "no such file";
		return 1;
	}
	return 0;
}

int OpenOut(const string OutFile, ofstream &out) {
	out.open(OutFile);
	if (!out.is_open()) {
		cerr << "no such file";
		return 1;
	}
	return 0;
}

int main(int argc, const char *argv[]) {

	ifstream in;
	ofstream out;
	
	if (argc == 3) {
		if (OpenIn(argv[1], in))
			return 0;
		if (OpenOut(argv[2], out))
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
