#include "Words.h"

void words::SortOut(ofstream &out) {

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

void words::MakeMap(string arg) {
	//if there is no element with this word in a map
	if (WordsList.find(arg) == WordsList.end())
		WordsList.insert(WordsList.end(), make_pair(arg, 1));
	else
		//if we have an element with this word in a map
		WordsList[arg]++;

	count++;
	return;
}

string words::EraseChar(std::string arg, char ch, int pos) {
	if (arg[pos] == ch)
		arg.erase(arg.find(ch));
	return arg;
}

string words::CleanString(string arg) {

	for (auto &i : arg) {
		if (!((i >= '0') && (i <= '9') || (i >= 'A') && (i <= 'Z') || (i >= 'a') && (i <= 'z')))
			arg.erase(arg.find(i));
	}
	return arg;
}

string words::ToLower(string arg) {
	setlocale(LC_ALL, "Russian");
	transform(arg.begin(), arg.end(), arg.begin(), tolower);
	return arg;
}

int words::CountWords(ifstream &in, ofstream &out) {

	while (!in.eof()) {
		string arg;
		//get one word
		getline(in, arg, ' ');
		//translate all symbols from the word to small register
		//and delete all punctuation marks
		arg = ToLower(arg);
		arg = CleanString(arg);
		if ((arg[0] != '\n') && (arg.size() != 0))
			//create a map with words and their frequency
			MakeMap(arg);
	}

	//put wors and their frequense in descending order to the csv file 
	SortOut(out);
	return 0;

}
