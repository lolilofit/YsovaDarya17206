#ifndef _TRITARR_
#define _TRITARR_
#include"OneTrit.h"
#include<iostream>
#include<vector>
#include<unordered_map>

class TritArr
{
	//const int size_t = (sizeof(unsigned int) * 4);
	int count = 0;
	int maxlen;

	int rest(int pos);

	void _resize(int index);

 public:
	 std::vector <unsigned int> arr;

	class Equal {
	 public:
		TritArr* p;
		int pos = -1;
		int value = -1;

		Equal(int position, int val);

		TritArr& operator=(const Trit &val);

		operator Trit() const;
	};
	
public:

	std::unordered_map< Trit, int, std::hash<int> > cardinality();

	TritArr(int length);

	~TritArr();

	void Trim(int last_index);

	size_t LastUnknown();

	size_t cardinality(Trit val);
	
	size_t capacity();

	void Shrink();

	int read(int pos) const;

	void SetTrit(int pos, Trit val);

	TritArr::Equal operator[](int pos);

};

bool operator==(TritArr::Equal trit_equal, Trit val);

#endif