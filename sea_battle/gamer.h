#ifndef GAMER_H
#define GAMER_H

#include<vector>
#include<map>
#include <ctime>
#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<list>
#include<conio.h>
#include<algorithm>
#include"optionparser.h"
#include "console_view.h"

enum Orientation : int { vertical = 0, horizontal = 1 };
enum Hit : int { no = 0, touched = 1, killed = 2 };
enum IsShip : int { no_ship = 0, yes = 1 };

class Gamer {


public:
	std::vector<std::vector<int>> field;
	Gamer();

	virtual std::vector<int> attack(std::vector<std::vector<int>> &my_turns) = 0;
	virtual void init_field() = 0;
	
	
	bool can_set(int x, int y, int num_palubs, int orientatation, std::vector<std::vector<int>> _field);

	~Gamer();
};

#endif
