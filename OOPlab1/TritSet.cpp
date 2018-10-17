#include "TritSet.h"
#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>


TritSet::TritSet(int length) {
	assert(length >= 0);

	//make set of unknown trits
	for (int i = 0; i < length / (sizeof(unsigned int) * 4) + rest(length); i++)
		set.push_back(0);
	count = length;
	maxlen = length;
}


TritSet::SetProxy::SetProxy(int position, TritSet *point) { pos = position, p = point}

//set all trits after trit with last_index position to unknown
void  TritSet::trim(int last_index) {
	for (int i = last_index; i < maxlen; i++)
		this->set_trir(i, static_cast<Trit>(0));
	maxlen = last_index + 1;
}

size_t TritSet::capacity() const{
	return this->maxlen;
}

size_t TritSet::lenght() const{

	//find the last true/false element
	for (int i = this->set.size() * sizeof(unsigned int) * 4; i >= 0; i--) {
		if (this->read(i) != Trit::Unknown)
			return i + 1;
	}
	return 0;
}

size_t TritSet::cardinality(Trit val) const{
	int count_val = 0;

	//find true/false trit and count them
	if (static_cast<int> (val) != 0) {
		for (int i = this->set.size() - 1; i >= 0; i--) {
			for (int j = (sizeof(unsigned int) * 4) - 1; j >= 0; j--) {
				if (this->read(i * (sizeof(unsigned int) * 4) + j) == val)
					count_val++;
			}
		}
	}
	else
		count_val = this->set.size()*(sizeof(unsigned int) * 4) - this->lenght();
	return count_val;
}

int TritSet::rest(int pos) {
	if (pos % (sizeof(unsigned int) * 4) != 0)
		return 1;
	return 0;
}

void TritSet::shrink() {
	//refresh last true/false element
	int maximum = std::max(static_cast<int>(this->lenght()), count);
	maxlen = maximum;
	//resize set
	this->set.resize(maximum / (sizeof(unsigned int) * 4) + rest(maximum));
}

//resize set of trits
void TritSet::_resize(int index) {
	this->set.resize(index);
}

//read trit from set of trits
Trit TritSet::read(int pos) const {
	if (this->set.size() * (sizeof(unsigned int) * 4) - 1 < pos)
		return 0;
	unsigned int point = this->set[pos / (sizeof(unsigned int) * 4)];
	return static_cast<int> (((point >> (2 * (sizeof(unsigned int) * 4) - 2 - 2 * (pos % (sizeof(unsigned int) * 4)))) & 1) + 2 * (1 & (point >> (2 * (sizeof(unsigned int) * 4) - 1 - 2 * (pos % (sizeof(unsigned int) * 4))))));
}

//set trit to the set of trits to necessary position
void TritSet::set_trir(int pos, Trit val) {
	const int size = sizeof(unsigned int) * 4;

	if (this->set.size()*size - 1 < pos) {
		//if set of trits have less than position elements
		if (val == Trit::Unknown)
			//no memory allocation
			return;
		if (val == Trit::True) {
			//memory allocation and writing trit to the set
			this->set.resize((pos + 1) / size + rest(pos));
			maxlen = pos + 1;

			//set 0 to nesessary bit and write firs and second bot of trit
			int invert = (this->set[pos / size] & (~(1 << ((2 * size - 1) - 2 * (pos % size)))));
			this->set[pos / size] = invert | (2 << ((2 * size - 2) - 2 * (pos % size)));
			this->set[pos / size] = (this->set[pos / size] & (~(1 << ((2 * size - 2) - 2 * (pos % size))))) | (1 << ((2 * size - 2) - 2 * (pos % size)));
		}
	}
	else {

		int num = static_cast <int> (val);

		//set 0 to nesessary bit and write firs and second bot of trit
		int invert = (this->set[pos / size] & (~(1 << ((2 * size - 1) - 2 * (pos % size)))));
		this->set[pos / size] = invert | ((num & 2) << ((2 * size - 2) - 2 * (pos % size)));

		invert = (this->set[pos / size] & (~(1 << ((2 * size - 2) - 2 * (pos % size)))));
		this->set[pos / size] = invert | ((num & 1) << ((2 * size - 2) - 2 * (pos % size)));
		this->lenght() > count ? maxlen = this->lenght() : maxlen = count;
	}
}

//brackets operator overload
TritSet::SetProxy TritSet::operator[](int pos) {
	//return an element of interior class with necessary position and element in this position
	SetProxy pack(pos, this);
	return pack;
}

//converting from element of interior class to trit from necessary position
TritSet::SetProxy::operator Trit() const {
	return this->p->read(pos);
}

//equality operator overload
TritSet& TritSet::SetProxy::operator=(const Trit &val) {
	p->set_trir(pos, val);
	return *p;
}

//double equality operator overload
bool operator==(TritSet::SetProxy trit_equal, Trit val) {
	bool res = 0;

	//get set of trits from the link in element of interior class
	TritSet trit_arr = *trit_equal.p;
	if (val == trit_arr.read(trit_equal.pos))
		res = 1;
	return res;
}

std::unordered_map< Trit, int, std::hash<Trit> > TritSet::cardinality() {
	//make unordered map with pairs of trit and their number in set
	std::unordered_map< Trit, int, std::hash<Trit> > result;
	int count_true = 0, count_false = 0;

	//count number of true and false trits
	for (int i = 0; i < this->lenght(); i++) {
		if (this->read(i) == Trit::False)
			count_false++;
		if (this->read(i) == Trit::True)
			count_true++;
	}


	std::pair<Trit, int> mypair_true(Trit::True, count_true);
	result.insert(mypair_true);

	std::pair<Trit, int> mypair_false(Trit::False, count_false);
	result.insert(mypair_false);

	std::pair<Trit, int> mypair_unknown(Trit::Unknown, this->set.size()*(sizeof(unsigned int) * 4) - this->lenght());
	result.insert(mypair_unknown);

	return result;
}


Trit operator[](int pos) const {
  return this->read(pos);
}
