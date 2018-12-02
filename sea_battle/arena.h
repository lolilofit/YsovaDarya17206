#ifndef ARENA_H
#define ARENA_H

#include<iostream>
#include<vector>
#include<string>
#include "console_view.h"
#include"gamer.h"
#include"create.h"

class Arena {
	int count_kills(std::vector<std::vector<int>> my_turns) {
		int count = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (my_turns[i][j] == 2)
					count++;
			}
		}

		return count;
	}

public:
	std::vector<std::vector<int>> turns_one;
	std::vector<std::vector<int>> turns_two;
	
	Arena() {
		turns_one.resize(10);
		for (int i = 0, _size = turns_one.size(); i < _size; i++) {
			turns_one[i].resize(10);
		}

		turns_two.resize(10);
		for (int i = 0, _size = turns_two.size(); i < _size; i++) {
			turns_two[i].resize(10);
		}

	}

	std::vector<std::vector<int>> get_field(int count) {
		if (count % 2)
			return turns_one;
		else
			return turns_two;
	}

	std::vector<int> turn(int &_gamer, Gamer *player) {
		
		std::vector<int> set_this;
		set_this.resize(2);

		if(_gamer%2 == 0)
		  set_this = player->attack(turns_one);
		else
			set_this = player->attack(turns_two);
		return set_this;
	}

	int num_ships() {
		if (count_kills(turns_one) >= 20)
			return 1;
		if (count_kills(turns_two) >= 20)
			return 2;
		return 0;

	}
	
	void hit(int count, std::vector<int> set_this, int val) {
		if (count % 2 == 0)
			turns_one[set_this[0]][set_this[1]] = val;
		else
		    turns_two[set_this[0]][set_this[1]] = val;
	}

	~Arena() {
		int _size;
		for (int i = 0, _size = turns_one.size(); i < _size; i++)
			turns_one[i].clear();
		turns_one.clear();

		for (int i = 0, _size = turns_two.size(); i < _size; i++)
			turns_two[i].clear();
		turns_two.clear();

	}
};

#endif
