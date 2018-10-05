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


string words::ToLower(string arg) {
	setlocale(LC_ALL, "Russian");
	transform(arg.begin(), arg.end(), arg.begin(), tolower);
	return arg;
}

int words::CountWords(ifstream &in, ofstream &out) {
	string one_word;

	while (!in.eof()) {
		char ch = in.get();
		if ((ch >= '0') && (ch <= '9') || (ch >= 'A') && (ch <= 'Z') || (ch >= 'a') && (ch <= 'z'))
			one_word = one_word + ch;
		else {
			if (one_word.size()) {
				one_word = ToLower(one_word);
				WordsList[one_word]++;
				count++;
				one_word.clear();
			}
		}
	}

	SortOut(out);
	return 0;

}
