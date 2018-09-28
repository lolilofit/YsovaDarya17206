#ifndef _TRITARR_
#define _TRITARR_
#include"OneTrit.h"
#include<iostream>
#include<vector>

class TritArr
{
	const int size_t = (sizeof(unsigned int)) * 4;
	int count = 0;
	
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
	TritArr(int length);

	~TritArr();

	void Trim(int last_index);

	int LastUnknown();

	int cardinality(Trit val);
	
	int capacity();

	void Shrink();

	int read(int pos) const;

	void SetTrit(int pos, Trit val);

	TritArr::Equal operator[](int pos);

	//Trit operator[](const int pos) const;
};

bool operator==(TritArr::Equal trit_equal, Trit val);

#endif