#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
#include <iomanip>

using namespace std;

class words {

	int count = 0;
	map <string, int> WordsList;

	void SortOut(ofstream &out);

	string ToLower(string arg);



public:
	int CountWords(ifstream &in, ofstream &out);

};
