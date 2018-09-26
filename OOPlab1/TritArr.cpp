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
}

TritArr::~TritArr() {
	arr.clear();
}

TritArr::Equal::Equal(int position, int val) { pos = position; value = val; }

void  TritArr::Trim(int last_index) {
	this->arr.resize(last_index);
}

int TritArr::capacity() {
	return this->arr.size();
}

int TritArr::LastUnknown() {
	for (int i = this->arr.capacity(); i > 0; i--) {
		for (int j = size_t-1; j >= 0; j--) {
			if (this->read(i * size_t + j) > 0)
				return size_t * i + j + 1;
		}
	}
	return -1;
}

int TritArr::cardinality(Trit val) {
	int count_val = 0;
	if (static_cast<int> (val) != 0) {
		for (int i = this->arr.capacity(); i > 0; i--) {
			for (int j = size_t-1; j >= 0; j--) {
				if (this->read(i * size_t + j) == static_cast<int> (val))
					count_val++;
			}
		}
	}
	else
		count_val = this->arr.capacity() - this->LastUnknown();
	return count_val;
}

void TritArr::Shrink() {
	for (int i = this->arr.capacity(); i > count; i--) {
		if (this->arr[i] > 0) {
			for (int j = size_t-1; j >= 0; j--) {
				if (this->read(i * size_t + j) == 1 || this->read(i * size_t + j) == 2) {
					this->arr.resize(size_t * i + j);
					return;
				}
			}
		}
	}
	this->arr.resize(count);
}

int TritArr::read(int pos) {
	if (this->arr.capacity() * size_t < pos)
		return 0;
	unsigned int point = this->arr[pos / size_t];
	return static_cast<int> (((point >> (2*size_t - 2 - 2 * (pos % size_t))) & 1) + 2 * (1 & (point >> (2*size_t - 1 - 2 * (pos % size_t)))));
}

void TritArr::SetTrit(int pos, Trit val) {
	if (this->arr.capacity() * size_t < pos) {
		if (val == Trit::Unknown)
			return;
		if (val == Trit::True) {
			this->arr.resize(pos / size_t);
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


TritArr& TritArr::Equal::operator=(const Trit &val) {
	p->SetTrit(pos, val);
	return *p;
}

bool operator==(TritArr trit_arr, Trit val) {
	bool res = 0;
	if (static_cast<int>(val) == trit_arr.arr[trit_arr.arr.capacity() - 1])
		res = 1;
	trit_arr.arr.erase(trit_arr.arr.begin() + trit_arr.arr.capacity() - 2, trit_arr.arr.end());
	return res;
}

