#include "LogicOp.h"
#include "TritArr.h"
#include<iostream>
#include<algorithm>

//logic operators for set of trits

TritSet operator&(TritSet &first, TritSet &second) {
	const int size = sizeof(unsigned int) * 4;
	
	//size of new trit
	int minimum = std::min(first.lenght(), second.lenght());
	TritSet res_arr(std::min(first.capacity(), second.capacity()));

	for (int i = 0; i < minimum; i++) {
		for (int j = 0; j < size; j++) {
			//read each trit
			int first_trit = first.read(i * size + j);
			int	second_trit = second.read(i * size + j);

			//make new trit which is a result of operation
			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit new_trits = static_cast <Trit> (second_trit);
			Trit res_trit = new_tritf & new_trits;

			//write this trit to the new set of trits
			res_arr.set_trir(i * size + j, res_trit);
		}
	}
	return res_arr;
}

TritSet operator|(TritSet &first, TritSet &second) {
	const int size_t = sizeof(unsigned int) * 4;
	
	//size of new trit
	int maximum = std::max(first.lenght(), second.lenght());
	int first_trit, second_trit;

	TritSet res_arr(std::max(first.capacity(), second.capacity()));

	for (int i = 0; i < maximum; i++) {
		for (int j = 0; j < size_t; j++) {
		
			//read each trit
			first_trit = first.read(i * size_t + j);
			second_trit = second.read(i * size_t + j);
			
			//make new trit which is a result of operation
			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit new_trits = static_cast <Trit> (second_trit);
			Trit res_trit = new_tritf | new_trits;

			//write this trit to the new set of trits
			res_arr.set_trir(i * size_t + j, res_trit);
		}
	}
	return res_arr;
}

TritSet operator~(TritSet &first) {
	const int size = sizeof(unsigned int) * 4;

	TritSet res_arr(first.capacity());

	for (int i = 0; i < first.lenght(); i++) {
		for (int j = 0; j < size; j++) {
			//read trit
			int first_trit = first.read(i * size + j);

			//make new trit which is a result of operation
			Trit new_tritf = static_cast <Trit> (first_trit);
			Trit res_trit = ~new_tritf;
			//write this trit to the new set of trits
			res_arr.set_trir(i * size + j, res_trit);
		}
	}
	return res_arr;
}
