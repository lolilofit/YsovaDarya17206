#ifndef _TRITSET_
#define _TRITSET_
#include"OneTrit.h"
#include<iostream>
#include<vector>
#include<unordered_map>

class SetProxy;

class TritSet
{
	//the number of original size
	int count = 0;
	//last true/false element
	int maxlen;
	std::vector <unsigned int> set;

	int rest(int pos);

	void _resize(int index);

public:
	TritSet();

	std::unordered_map< Trit, int, std::hash<Trit> > cardinality();

	TritSet(int length);

	void trim(int last_index);

	size_t lenght();

	size_t cardinality(Trit val);
	
	size_t capacity();

	void shrink();

	Trit read(int pos) const;

	void set_trir(int pos, Trit val);

	SetProxy operator[](int pos);
    
	Trit operator[](int pos) const;

};

class SetProxy : public TritSet {
	int pos = -1;
	//value in this position
	TritSet * p;
	//position we want to set to or read from

	SetProxy(int position, TritSet * ptr);
	friend TritSet;

public:

	TritSet & operator=(const Trit &val);

	operator Trit() const;
};

bool operator==(const int val, Trit trit);


#endif
