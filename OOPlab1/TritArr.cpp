#include "TritArr.h"
#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>

TritArr::TritArr(int length) {
	assert(length >= 0);

	for (int i = 0; i < length; i++)
		arr.push_back(0);
	count = length;
	maxlen = length;
}

TritArr::~TritArr() {
	arr.clear();
}

TritArr::Equal::Equal(int position, int val) { pos = position; value = val; }

void  TritArr::Trim(int last_index) {
	this->arr.resize(last_index);
	maxlen = last_index;
}

int TritArr::capacity() {
	return this->maxlen;
}

int TritArr::LastUnknown() {
	for (int i = this->arr.size() - 1; i >= 0; i--) {
		for (int j = size_t-1; j >= 0; j--) {
			if (this->read(i * size_t + j) > 0)
				return size_t * i + j + 1;
		}
	}
	return 0;
}

int TritArr::cardinality(Trit val) {
	int count_val = 0;
	if (static_cast<int> (val) != 0) {
		for (int i = this->arr.size(); i > 0; i--) {
			for (int j = size_t-1; j >= 0; j--) {
				if (this->read(i * size_t + j) == static_cast<int> (val))
					count_val++;
			}
		}
	}
	else
		count_val = this->arr.size() - this->LastUnknown();
	return count_val;
}

void TritArr::Shrink() {
	for (int i = this->arr.size(); i > count; i--) {
		if (this->arr[i] > 0) {
			for (int j = size_t-1; j >= 0; j--) {
				if (this->read(i * size_t + j) == 1 || this->read(i * size_t + j) == 2) {
					this->arr.resize(size_t * i + j + 1);
					maxlen = size_t * i + j;
					return;
				}
			}
		}
	}
	this->arr.resize(count);
}

int TritArr::read(int pos) const{
	if (this->arr.size() * size_t - 1 < pos)
		return 0;
	unsigned int point = this->arr[pos / size_t];
	return static_cast<int> (((point >> (2*size_t - 2 - 2 * (pos % size_t))) & 1) + 2 * (1 & (point >> (2*size_t - 1 - 2 * (pos % size_t)))));
}

void TritArr::SetTrit(int pos, Trit val) {
	if (this->arr.size() * size_t - 1 < pos) {
		if (val == Trit::Unknown)
			return;
		if (val == Trit::True) {
			this->arr.resize(pos / size_t );
			maxlen = pos / size_t;
			this->arr[pos / size_t] = this->arr[pos / size_t] & 1;
		}
	}
	else {
		
		int num = static_cast <int> (val);
		this->arr[pos / size_t] = (this->arr[pos / size_t] & (~(1 << ((2* size_t - 1) - 2 * (pos % size_t))))) | (num & 2);
		this->arr[pos / size_t] = (this->arr[pos / size_t] & (~(1 << ((2*size_t - 2) - 2 * (pos % size_t))))) | (num & 1);
	}
}

TritArr::Equal TritArr::operator[](int pos) {
	Equal pack(pos, this->read(pos));
	pack.p = this;
	return pack;
}

TritArr::Equal::operator Trit() const {
	return static_cast<Trit> (this->p->read(pos));
}

TritArr& TritArr::Equal::operator=(const Trit &val) {
	p->SetTrit(pos, val);
	return *p;
}

bool operator==(TritArr::Equal trit_equal, Trit val) {
	bool res = 0;
	TritArr trit_arr = *trit_equal.p;
	if (static_cast<int>(val) == trit_arr.read(trit_equal.pos))
		res = 1;
	return res;
}

