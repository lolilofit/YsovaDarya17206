#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
#include <iomanip>
#include"clean.h"

using namespace std;

class words {

	int count = 0;
	map <string, int> WordsList;
    
	void SortOut(ofstream &out) {

		multimap<int, string> SortMap;
		//make sorted map
		for (auto cur = WordsList.begin(); cur != WordsList.end(); ++cur)
			SortMap.insert(SortMap.end(), make_pair(cur->second, cur->first));
		for (auto cur = SortMap.rbegin(); cur != SortMap.rend(); ++cur) {
			double persent = (100.000*cur->first) / count;
			out << cur->second << " " << cur->first << " " << fixed << setprecision(3) << persent << "%" << endl;
		}

		return;
	}

	void MakeMap(string arg) {
		//if there is no element with this word in a map
		if (WordsList.find(arg) == WordsList.end())
			WordsList.insert(WordsList.end(), make_pair(arg, 1));
		else
			//if we have an element with this word in a map
			(WordsList.find(arg))->second++;

		count++;
		return;
	}
public:
	int CountWords(ifstream &in, ofstream &out) {
		
		while (!in.eof()) {
			string arg;
			//get one word
			getline(in, arg, ' ');
			//translate all symbols from the word to small register
			//and delete all punctuation marks
			arg = cleanstring::ToLower(arg);
			arg = cleanstring::CleanString(arg);
			if ((arg[0] != '\n') && (arg.size() != 0))
				//create a map with words and their frequency
				MakeMap(arg);
		}

		//put wors and their frequense in descending order to the csv file 
		SortOut(out);
		return 0;

	}

};

void OpenIn(const string InputFile, ifstream &in) {
	
	in.open(InputFile);
	if (!in.is_open()) 
		cerr << "no such file";
	return;
}

void OpenOut(const string OutFile, ofstream &out) {
	out.open(OutFile);
	if (!out.is_open()) 
		cerr << "no such file";
	return;
}

int main(int argc, const char *argv[]) {
	ifstream in;
	ofstream out;
	if (argc == 3) {
		OpenIn(argv[1], in);
		//in.open(argv[1]);
	    OpenOut(argv[2], out);
		//out.open(argv[2]);
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
