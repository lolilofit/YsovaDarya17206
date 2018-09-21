#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>
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

	 void shrink(int val) {
		 for (int i = this->arr.capacity(); i > count; i--) {
			 if (this->arr[i] > 0) {
				 for (int j = 3; j >= 0; j--) {
					 if (this->read(i * 4 + j) == (1 || 2)) {
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
		unsigned int point = this->arr[pos/4];
 		return static_cast<int> (((point >> (6 - 2 * (pos % 8))) & 1) + 2 * (1 & (point >> (7 - 2 * (pos % 8)))));
	}

	void SetTrit(int pos, Trit val) {
		if (this->arr.capacity() < pos) {
			if (val == Trit::Unknown)
			 return;
			if (val == Trit::True) {
				this->arr.resize(pos / 4); 
				this->arr[pos / 4] = this->arr[pos / 4] & 1;
			}
		}
		else {
			int num = static_cast <int> (val);
			this->arr[pos / 4] = (this->arr[pos / 4] & (~(1 << (6 - 2 * (pos % 8))))) | (num & 2);
			this->arr[pos / 4] = (this->arr[pos / 4] & (~(1 << (5 - 2 * (pos % 8))))) | (num & 1);
		}
	}
};


TritArr operator&(TritArr &first, TritArr &second) {
	int minimum = min(first.arr.capacity(), second.arr.capacity());
	TritArr res_arr(minimum);

	for (int i = 0; i < minimum; i++) {
			for (int j = 0; j < 4; j++) {
				int first_trit = first.read(i * 4 + j);
				int	second_trit = second.read(i * 4 + j);
				
				Trit new_tritf = static_cast <Trit> (first_trit);
				Trit new_trits = static_cast <Trit> (second_trit);
				Trit res_trit = new_tritf&new_trits;
				
				res_arr.SetTrit(i*4+j, res_trit);
      		}
		}
	return res_arr;
	}
 
TritArr operator|(TritArr &first, TritArr &second) {
	int minimum = min(first.arr.capacity(), second.arr.capacity());
	TritArr res_arr(minimum);

	for (int i = 0; i < minimum; i++) {
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

int main() {
	TritArr ar1(3);
	TritArr ar2(2);
	ar1.arr[0] = 3;
	ar1.arr[1] = 2;
	ar1.arr[2] = 2;

	ar2.arr[1] = 0;
	ar2.arr[0] = 1;
	TritArr tr = ar1 & ar2;
	return 0;
}