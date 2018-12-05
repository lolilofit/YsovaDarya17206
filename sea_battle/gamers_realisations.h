#ifndef GAMERS_REALISATIONS

#define GAMERS_REALISATIONS
#include"gamer.h"

class OptimalGamer : public Gamer {
	std::vector<int> palubs;
	int cur_x = 3, cur_y = 0, cur_ship_x = 3, cur_ship_y = 0, ship_left = cur_x - 1, ship_right = cur_x + 1, ship_down = cur_y - 1, ship_up = cur_y + 1;
	int mistake(int x, int y);

	std::list<std::list<int>> free_place(int field_orientation, int side, int pal);

	void next_turn(int pal, std::vector<std::vector<int>> &my_turns);

public:
	std::vector<int> attack(std::vector<std::vector<int>> &my_turns);

	void init_field();
};

class ConsoleGamer : public Gamer {
public:
	std::vector<int> attack(std::vector<std::vector<int>> &my_turns);

	void init_field();
};

class random_stragegyGamer : public Gamer {

public:
	std::vector<int> attack(std::vector<std::vector<int>> &my_turns);

	void init_field();
};



#endif
