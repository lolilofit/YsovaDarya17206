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

	class SetProxy {  //friend
		 TritSet * p;
		 //position we want to set to or read from
		 int pos = -1;
		
		  SetProxy(int position, TritSet *point);
		
	 public:
		TritSet& operator=(const Trit &val);

		operator Trit() const;
	};
	
public:

	std::unordered_map< Trit, int, std::hash<Trit> > cardinality();

	TritSet(int length);

	void trim(int last_index);

	size_t lenght() const;

	size_t cardinality(Trit val) const;
	
	size_t capacity() const;

	void shrink();

	int read(int pos) const;

	void set_trir(int pos, Trit val);

	TritSet::SetProxy operator[](int pos);
	//Trit operator[](int pos) const;

};

bool operator==(TritSet::SetProxy trit_equal, Trit val);

#endif
