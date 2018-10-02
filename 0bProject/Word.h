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

	void MakeMap(string arg);

	string EraseChar(std::string arg, char ch, int pos);

	string CleanString(string arg);

	string ToLower(string arg);



public:
	int CountWords(ifstream &in, ofstream &out);

};
