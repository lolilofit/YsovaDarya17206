#ifndef ARENA_H
#define ARENA_H

#include<iostream>
#include<vector>
#include<string>
#include "console_view.h"
#include"gamer.h"
#include"create.h"

class Arena {
	int count_kills(std::vector<std::vector<int>> my_turns);
public:
	std::vector<std::vector<int>> turns_one;
	std::vector<std::vector<int>> turns_two;
	
	Arena();
	
	std::vector<int> turn(int &_gamer, Gamer *player);

	int num_ships();

	void hit(int count, std::vector<int> set_this, int val);

	~Arena();
};

#endif
