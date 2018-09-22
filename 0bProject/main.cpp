#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>
#include<unordered_map>

enum class Trit : unsigned int { False = 1, Unknown = 0, True = 3 };

using namespace std;


Trit operator &(Trit &first, Trit &second) {
	if (first == Trit::False || second == Trit::False)
		return Trit::False;
	if (first == Trit::True && second == Trit::True)
		return Trit::True;
	return Trit::Unknown;
}

Trit operator |(Trit &first, Trit &second) {
	if (first == Trit::True || second == Trit::True)
		return Trit::True;
	if (first == Trit::False && second == Trit::False)
		return Trit::False;
	return Trit::Unknown;

}

Trit operator ~(Trit &elem) {
	if (elem == Trit::True)
		return Trit::False;
	if (elem == Trit::False)
		return Trit::True;
	return Trit::Unknown;

}




class TritArr
{
	int count = 0;
public:
	vector <unsigned int> arr;

public:
	TritArr(int length) {
		assert(length >= 0);

		for (int i = 0; i < length; i++)
			arr.push_back(0);
		count = length;
	}


	~TritArr() {
		arr.clear();
	}

	void Trim(int last_index) {
		this->arr.resize(last_index);
	}

	int LastUnknown() {
		for (int i = this->arr.capacity(); i > 0; i--) {
			for (int j = 3; j >= 0; j--) {
				if (this->read(i * 4 + j) > 0)
					return 4 * i + j + 1;	
			}
		}
		return -1;
	}

	int cardinality(Trit val) {
		int count_val = 0;
		if (static_cast<int> (val) != 0) {
			for (int i = this->arr.capacity(); i > 0; i--) {
				for (int j = 3; j >= 0; j--) {
					if (this->read(i * 4 + j) == static_cast<int> (val))
						count_val++;
				}
			}
		}
		else
			count_val = this->arr.capacity() - this->LastUnknown();
		return count_val;
	}

	void Shrink() {
		for (int i = this->arr.capacity(); i > count; i--) {
			if (this->arr[i] > 0) {
				for (int j = 3; j >= 0; j--) {
					if (this->read(i * 4 + j) == 1 || this->read(i * 4 + j) == 2) {
						this->arr.resize(4 * i + j);
						return;
					}
				}
			}
		}
		this->arr.resize(count);
	}

	int read(int pos) {
		if (this->arr.capacity() < pos)
			return 0;
		unsigned int point = this->arr[pos / 4];
		return static_cast<int> (((point >> (6 - 2 * (pos % 4))) & 1) + 2 * (1 & (point >> (7 - 2 * (pos % 4)))));
	}

	void SetTrit(int pos, Trit val) {
		if (this->arr.capacity()*4 < pos) {
			if (val == Trit::Unknown)
				return;
			if (val == Trit::True) {
				this->arr.resize(pos / 4);
				this->arr[pos / 4] = this->arr[pos / 4] & 1;
			}
		}
		else {
			int num = static_cast <int> (val);
			this->arr[pos / 4] = (this->arr[pos / 4] & (~(1 << (7 - 2 * (pos % 4))))) | (num & 2);
			this->arr[pos / 4] = (this->arr[pos / 4] & (~(1 << (6 - 2 * (pos % 4))))) | (num & 1);
		}
	}

	TritArr operator[](int pos) {
		this->arr.push_back(pos);
		this->arr.push_back(this->read(pos));
		return *this;
	}

	void operator=(Trit val) {
		this->SetTrit(this->arr[arr.capacity() - 2], val);
	    this->arr.erase(this->arr.begin() + this->arr.capacity() - 2, this->arr.end());
	}

};

bool operator==(TritArr trit_arr, Trit val) {
	bool res = 0;
	if (static_cast<int>(val) == trit_arr.arr[trit_arr.arr.capacity()-1])
		res = 1;
	trit_arr.arr.erase(trit_arr.arr.begin()+ trit_arr.arr.capacity() - 2, trit_arr.arr.end());
	return res;
}


TritArr operator&(TritArr &first, TritArr &second) {
	int minimum = min(first.arr.capacity(), second.arr.capacity());
	TritArr res_arr(minimum);

	for (int i = 0; i < minimum; i++) {
		for (int j = 0; j < 4; j++) {
			int first_trit = first.read(i * 4 + j);
			int	second_trit = second.read(i * 4 + j);

			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit new_trits = static_cast <Trit> (second_trit);
			Trit res_trit = new_tritf & new_trits;

			res_arr.SetTrit(i * 4 + j, res_trit);
		}
	}
	return res_arr;
}

TritArr operator|(TritArr &first, TritArr &second) {
	int maximum = max(first.arr.capacity(), second.arr.capacity());
	TritArr res_arr(maximum);

	for (int i = 0; i < maximum; i++) {
		for (int j = 0; j < 4; j++) {
			int first_trit = first.read(i * 4 + j);
			int	second_trit = second.read(i * 4 + j);

			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit new_trits = static_cast <Trit> (second_trit);
			Trit res_trit = new_tritf | new_trits;

			res_arr.SetTrit(i * 4 + j, res_trit);
		}
	}
	return res_arr;
}

TritArr operator~(TritArr &first) {

	TritArr res_arr(first.arr.capacity());
	for (int i = 0; i < first.arr.capacity(); i++) {
		for (int j = 0; j < 4; j++) {
			int first_trit = first.read(i * 4 + j);

			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit res_trit = ~new_tritf;
			res_arr.SetTrit(i * 4 + j, res_trit);
		}
	}
	return res_arr;
}

/*
 int cardinality(unordered_map<Trit, int, hash<int>> trit_map, Trit val) {
	if(static_cast <int> (val) != 0)
    	return trit_map.count(val);
	int count_val = 0, i =0;
	for (auto item : trit_map) {
		i++;
		if (item.first != static_cast <Trit> (0))
			count_val = i+1;
	}
	return (trit_map.size() - count_val);
} 
*/

int main() {
	TritArr ar1(3);
	TritArr ar2(2);
	ar1.arr[0] = 3;
	ar1.arr[1] = 3;
	ar1.arr[2] = 2;
	

	ar2.arr[1] = 0;
	ar2.arr[0] = 1;

	return 0;
}
