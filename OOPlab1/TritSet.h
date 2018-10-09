#ifndef _TRITSET_
#define _TRITSET_
#include"OneTrit.h"
#include<iostream>
#include<vector>
#include<unordered_map>

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
	 //set of trits

	class SetProxy {
	 public:
		 TritSet * p;
		 //position we want to set to or read from
		int pos = -1;
		//value in this position
		int value = -1;

		SetProxy(int position, int val);

		//Equal(const Equal &src) : pos(src.pos), value(src.value);

		TritSet& operator=(const Trit &val);

		operator Trit() const;
	};
	
public:

	std::unordered_map< Trit, int, std::hash<Trit> > cardinality();

	TritSet(int length);

	~TritSet();

	void trim(int last_index);

	size_t lenght();

	size_t cardinality(Trit val);
	
	size_t capacity();

	void shrink();

	int read(int pos) const;

	void set_trir(int pos, Trit val);

	TritSet::SetProxy operator[](int pos);

};

bool operator==(TritSet::SetProxy trit_equal, Trit val);

#endif
