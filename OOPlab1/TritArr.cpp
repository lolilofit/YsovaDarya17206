#include "TritArr.h"
#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>

TritArr::TritArr(int length) {
    assert(length >= 0);
    
    for (int i = 0; i < length/ (sizeof(unsigned int) * 4) + rest(length); i++)
        arr.push_back(0);
    count = length;
    maxlen = length;
}

TritArr::~TritArr() {
    arr.clear();
}

TritArr::Equal::Equal(int position, int val) { pos = position; value = val; }

void  TritArr::Trim(int last_index) {
	for (int i = last_index; i < maxlen; i++)
		this->SetTrit(i, static_cast<Trit>(0));
		maxlen = last_index + 1;
}

size_t TritArr::capacity() {
    return this->maxlen;
}

size_t TritArr::LastUnknown() {
    
	for (int i = maxlen - 1; i >= 0; i--) {
		if (this->read(i) > 0)
			return i + 1;
	}
    return 0;
}

size_t TritArr::cardinality(Trit val) {
    int count_val = 0;

    if (static_cast<int> (val) != 0) {
        for (int i = this->arr.size() - 1; i >= 0; i--) {
            for (int j = (sizeof(unsigned int) * 4) -1; j >= 0; j--) {
                if (this->read(i * (sizeof(unsigned int) * 4) + j) == static_cast<int> (val))
                    count_val++;
            }
        }
    }
    else
        count_val = this->arr.size()*(sizeof(unsigned int) * 4) - this->LastUnknown();
    return count_val;
}

int TritArr::rest(int pos) {
	if (pos% (sizeof(unsigned int) * 4) != 0)
		return 1;
	return 0;
}

void TritArr::Shrink() {
	int maximum = std::max(static_cast<int>(this->LastUnknown()), count);
	maxlen = maximum;
	this->arr.resize(maximum/ (sizeof(unsigned int) * 4) + rest(maximum));
}

void TritArr::_resize(int index) {
	this->arr.resize(index);
}

int TritArr::read(int pos) const{
    if (this->arr.size() * (sizeof(unsigned int) * 4) - 1 < pos)
        return 0;
    unsigned int point = this->arr[pos / (sizeof(unsigned int) * 4)];
    return static_cast<int> (((point >> (2* (sizeof(unsigned int) * 4) - 2 - 2 * (pos % (sizeof(unsigned int) * 4)))) & 1) + 2 * (1 & (point >> (2* (sizeof(unsigned int) * 4) - 1 - 2 * (pos % (sizeof(unsigned int) * 4))))));
}

void TritArr::SetTrit(int pos, Trit val) {
	
    if (this->arr.size()*(sizeof(unsigned int) * 4) - 1 < pos) {
        if (val == Trit::Unknown)
            return;
        if (val == Trit::True) {
			this->arr.resize((pos+1) / (sizeof(unsigned int) * 4) + rest(pos));
            maxlen = pos + 1;

			this->arr[pos / (sizeof(unsigned int) * 4)] = (this->arr[pos / (sizeof(unsigned int) * 4)] & (~(1 << ((2 * (sizeof(unsigned int) * 4) - 1) - 2 * (pos % (sizeof(unsigned int) * 4)))))) | (2 << ((2 * (sizeof(unsigned int) * 4) - 2) - 2 * (pos % (sizeof(unsigned int) * 4))));
			this->arr[pos / (sizeof(unsigned int) * 4)] = (this->arr[pos / (sizeof(unsigned int) * 4)] & (~(1 << ((2 * (sizeof(unsigned int) * 4) - 2) - 2 * (pos % (sizeof(unsigned int) * 4)))))) | (1 << ((2 * (sizeof(unsigned int) * 4) - 2) - 2 * (pos % (sizeof(unsigned int) * 4))));
        }
    }
    else {

        int num = static_cast <int> (val);
        this->arr[pos / (sizeof(unsigned int) * 4)] = (this->arr[pos / (sizeof(unsigned int) * 4)] & (~(1 << ((2* (sizeof(unsigned int) * 4) - 1) - 2 * (pos % (sizeof(unsigned int) * 4)))))) | ((num & 2) << ((2 * (sizeof(unsigned int) * 4) - 2) - 2 * (pos % (sizeof(unsigned int) * 4))));
        this->arr[pos / (sizeof(unsigned int) * 4)] = (this->arr[pos / (sizeof(unsigned int) * 4)] & (~(1 << ((2* (sizeof(unsigned int) * 4) - 2) - 2 * (pos % (sizeof(unsigned int) * 4)))))) | ((num & 1) << ((2 * (sizeof(unsigned int) * 4) - 2) - 2 * (pos % (sizeof(unsigned int) * 4))));
		maxlen < pos ? maxlen = pos + 1 : maxlen = maxlen;
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

std::unordered_map< Trit, int, std::hash<int> > TritArr::cardinality() {
	std::unordered_map< Trit, int, std::hash<int> > result;
	int count_true = 0, count_false = 0;

	for (int i = 0; i < this->LastUnknown(); i++) {
		if (this->read(i) == 1)
			count_false++;
		if (this->read(i) == 3)
			count_true++;
	}

	std::pair<Trit, int> mypair_true (Trit::True, count_true);
	result.insert(mypair_true);
	/*
	std::pair<Trit, int> mypair_false(Trit::False, count_false);
	result.insert(mypair_false);
    
	std::pair<Trit, int> mypair_unknown(Trit::Unknown, this->arr.size()*(sizeof(unsigned int) * 4) - this->LastUnknown());
	result.insert(mypair_unknown);
	*/
	return result;
	return result;
}


