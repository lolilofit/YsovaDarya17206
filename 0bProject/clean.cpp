#include"clean.h"
#include<algorithm>

using namespace std;
namespace cleanstring {
	string ToLower(string arg) {
		setlocale(LC_ALL, "Russian");
		transform(arg.begin(), arg.end(), arg.begin(), tolower);
		return arg;
	}

	string EraseChar(string arg, char ch, int pos) {
		if (arg[pos] == ch)
			arg.erase(arg.find(ch));
		return arg;
	}

	string CleanString(string arg) {
		char punctuation[11] = { '!', '?', ',', '.', ';', ':', ')', '\n', '—', '(' };
		for (int i = 0; i < 10; i++) {
			if (arg.size() > 0) {
				if (i < 8)
					arg = EraseChar(arg, punctuation[i], arg.size() - 1);
				else
					arg = EraseChar(arg, punctuation[i], 0);
			}
		}
		return arg;
	}
}
