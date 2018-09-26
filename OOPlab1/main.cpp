#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>
#include<unordered_map>
#include "OneTrit.h"
#include "TritArr.h"
#include "LogicOp.h"

using namespace std;


/*
int cardinality(unordered_map<Trit, int, hash<int>> trit_map, Trit val) {
if(static_cast <int> (val) != 0)
return trit_map.count(val);
int count_val = 0, i =0;
for (auto item : trit_map) {
i++;
if (item.first != static_cast <Trit> (0))
count_val = i+1;
}
return (trit_map.size() - count_val);
}
*/




int main() {
	TritArr ar1(3);
	//TritArr ar2(2);
	ar1.arr[0] = 3;
	ar1.arr[1] = 3;
	ar1.arr[2] = 2;


	//ar2.arr[1] = 0;
	//ar2.arr[0] = 1;
	ar1[15] = Trit::False;

	return 0;
}