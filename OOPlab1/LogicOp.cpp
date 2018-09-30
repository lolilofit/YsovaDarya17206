#include "LogicOp.h"
#include "TritArr.h"
#include<iostream>
#include<algorithm>


TritArr operator&(TritArr &first, TritArr &second) {
	const int size_t = sizeof(unsigned int) * 4;

	int minimum = std::min(first.arr.size(), second.arr.size());
	TritArr res_arr(std::min(first.capacity(), second.capacity()));

	for (int i = 0; i < minimum; i++) {
		for (int j = 0; j < size_t; j++) {
			int first_trit = first.read(i * size_t + j);
			int	second_trit = second.read(i * size_t + j);

			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit new_trits = static_cast <Trit> (second_trit);
			Trit res_trit = new_tritf & new_trits;

			res_arr.SetTrit(i * size_t + j, res_trit);
		}
	}
	return res_arr;
}

TritArr operator|(TritArr &first, TritArr &second) {
	const int size_t = sizeof(unsigned int) * 4;
	
	int maximum = std::max(first.arr.size(), second.arr.size());
	int first_trit, second_trit;

	TritArr res_arr(std::max(first.capacity(), second.capacity()));

	for (int i = 0; i < maximum; i++) {
		for (int j = 0; j < size_t; j++) {
		
			first_trit = first.read(i * size_t + j);
			second_trit = second.read(i * size_t + j);
			
			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit new_trits = static_cast <Trit> (second_trit);
			Trit res_trit = new_tritf | new_trits;

			res_arr.SetTrit(i * size_t + j, res_trit);
		}
	}
	return res_arr;
}

TritArr operator~(TritArr &first) {
	const int size_t = sizeof(unsigned int) * 4;

	TritArr res_arr(first.capacity());
	for (int i = 0; i < first.arr.size(); i++) {
		for (int j = 0; j < size_t; j++) {
			int first_trit = first.read(i * size_t + j);

			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit res_trit = ~new_tritf;
			res_arr.SetTrit(i * size_t + j, res_trit);
		}
	}
	return res_arr;
}
