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

void  TritArr::Trim(int last_index) {
	this->arr.resize(last_index);
}

int TritArr::LastUnknown() {
	for (int i = this->arr.capacity(); i > 0; i--) {
		for (int j = 15; j >= 0; j--) {
			if (this->read(i * 16 + j) > 0)
				return 16 * i + j + 1;
		}
	}
	return -1;
}

int TritArr::cardinality(Trit val) {
	int count_val = 0;
	if (static_cast<int> (val) != 0) {
		for (int i = this->arr.capacity(); i > 0; i--) {
			for (int j = 15; j >= 0; j--) {
				if (this->read(i * 16 + j) == static_cast<int> (val))
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
			for (int j = 15; j >= 0; j--) {
				if (this->read(i * 16 + j) == 1 || this->read(i * 16 + j) == 2) {
					this->arr.resize(16 * i + j);
					return;
				}
			}
		}
	}
	this->arr.resize(count);
}

int TritArr::read(int pos) {
	if (this->arr.capacity() * 16 < pos)
		return 0;
	unsigned int point = this->arr[pos / 16];
	return static_cast<int> (((point >> (30 - 2 * (pos % 16))) & 1) + 2 * (1 & (point >> (31 - 2 * (pos % 16)))));
}

void TritArr::SetTrit(int pos, Trit val) {
	if (this->arr.capacity() * 16 < pos) {
		if (val == Trit::Unknown)
			return;
		if (val == Trit::True) {
			this->arr.resize(pos / 16);
			this->arr[pos / 16] = this->arr[pos / 16] & 1;
		}
	}
	else {
		int num = static_cast <int> (val);
		this->arr[pos / 16] = (this->arr[pos / 16] & (~(1 << (31 - 2 * (pos % 16))))) | (num & 2);
		this->arr[pos / 16] = (this->arr[pos / 16] & (~(1 << (30 - 2 * (pos % 16))))) | (num & 1);
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

TritArr::Equal::Equal(int position, int val) {pos = position; value = val; }
