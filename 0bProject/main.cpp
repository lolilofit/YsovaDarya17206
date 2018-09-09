#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

class words {

	int count;
	map <string, int> WordsList;

	
	void SortOut(string OutFile) {
		ofstream out;
		out.open(OutFile);
		if (!out.is_open())
			return;

		while (WordsList.begin() != WordsList.end()) {
			map<string, int>::iterator Cur = WordsList.begin();
			map<string, int>::iterator ToErase = WordsList.begin();
			
			//while map isn't empty
			while (Cur!= WordsList.end()) {
				//find element of a map with maximum frequency
				if (ToErase->second < Cur->second) 
					ToErase = Cur;
				Cur++;
			}

			float persent = (100/count)*ToErase->second;
			//put a word and his frequence in a file
			out << ToErase->first << " " << ToErase->second << " " <<persent<< "%"<<'\n';
			//delete an element of a map with maximum frecuency
			WordsList.erase(ToErase);
		}
		out.close();
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

	string CleanString(string arg) {
		setlocale(LC_ALL, "Russian");
		transform(arg.begin(), arg.end(), arg.begin(), tolower);
		if (arg.size() > 0) {
			if (arg[arg.size() - 1] == '\n')
				arg.erase(arg.find('\n'));
			if (arg[arg.size() - 1] == '!')
				arg.erase(arg.find('!'));
			if (arg[arg.size() - 1] == '?')
				arg.erase(arg.find('?'));
			if (arg[arg.size() - 1] == ',')
				arg.erase(arg.find(','));
			if (arg[arg.size() - 1] == ';')
				arg.erase(arg.find(';'));
			if (arg[arg.size() - 1] == ':')
				arg.erase(arg.find(':'));
			if (arg[arg.size() - 1] == '.')
				arg.erase(arg.find('.'));
			if (arg[0] == '—')
				arg.erase(arg.find('—'));
			if (arg[0] == '(')
				arg.erase(arg.begin());
			if (arg[arg.size() - 1] == ')') {
				arg.erase(arg.find(')'));
			}
		}
		return arg;
	}

public:
	int CountWords(string InputFile, string OutFile) {
		//open input file and check whether it opened
		ifstream in;
		in.open(InputFile);
		if (!in.is_open())
			return 0;

		count = 0;
		while (!in.eof()) {
			string arg;
			//get one word
			getline(in, arg, ' ');
			//translate all symbols from the word to small register
			//and delete all punctuation marks
			arg = CleanString(arg);
			if ((arg[0] != '\n') && (arg.size() != 0)) 
				//create a map with words and their frequency
				MakeMap(arg);
		}

		//put wors and their frequense in descending order to the csv file 
		SortOut(OutFile);
		in.close();
		return 0;
		
	}
	
};

int main() {
	string InputFile, OutFile;
	getline(cin, InputFile, ' ');
	getline(cin, OutFile);
	words st;
	st.CountWords(InputFile, OutFile);
	return 0;
}
