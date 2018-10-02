#ifndef _TRITARR_
#define _TRITARR_
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

	int rest(int pos);

	void _resize(int index);

 public:
	 //set of trits
	 std::vector <unsigned int> arr;

	class Equal {
	 public:
		 TritSet * p;
		 //position we want to set to or read from
		int pos = -1;
		//value in this position
		int value = -1;

		Equal(int position, int val);

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

	void SetTrit(int pos, Trit val);

	TritSet::Equal operator[](int pos);

};

bool operator==(TritSet::Equal trit_equal, Trit val);

#endif
