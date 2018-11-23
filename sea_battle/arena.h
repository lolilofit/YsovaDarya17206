#ifndef ARENA_H
#define ARENA_H

#include<iostream>
#include<vector>
#include<string>
#include "console_view.h"
#include"gamer.h"
#include"create.h"

class Arena {

public:
	std::vector<std::vector<int>> turns_one;
	std::vector<std::vector<int>> turns_two;
	Gamer* first;
	Gamer* second;

	Arena() = default;
	Arena(std::string name_one, std::string name_two) {
		srand(time(0));
		turns_one.resize(10);
		for (int i = 0, _size = turns_one.size(); i < _size; i++) {
			turns_one[i].resize(10);
		}

		turns_two.resize(10);
		for (int i = 0, _size = turns_two.size(); i < _size; i++) {
			turns_two[i].resize(10);
		}

		first = factory::get_instance().read(name_one)->make();
		first->init_field();
		second = factory::get_instance().read(name_two)->make();
		second->init_field();
	}

	void turn(int &_gamer) {
		int res;
		ConsoleView painter;
		std::vector<int> set_this;
		set_this.resize(2);

		if (!(_gamer % 2)) {
			painter.draw("attack!", first->field_for_draw(), turns_one);
			set_this = first->attack(turns_one);

			res = second->is_ship(set_this[0], set_this[1]);
			if (res == 1)
				turns_one[set_this[0]][set_this[1]] = 2;
			if (res == 2) {
					turns_one[set_this[0]][set_this[1]] = 2;
					_gamer++;
			}
			if(res==0)
				turns_one[set_this[0]][set_this[1]] = 1;
			
		}
		else {
			painter.draw("attack!", second->field_for_draw(), turns_two);
			set_this = second->attack(turns_two);

			res = first->is_ship(set_this[0], set_this[1]);
			if (res != 0) {
				turns_two[set_this[0]][set_this[1]] = 2;
				_gamer++;
			}
			if(res == 0)
				turns_two[set_this[0]][set_this[1]] = 1;
			
		}
	}

	int num_ships() {
		if (first->num_ships(turns_one) >= 20)
			return 1;
		if (second->num_ships(turns_two) >= 20)
			return 2;
		return 0;

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
