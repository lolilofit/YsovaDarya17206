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
#include"optionparser.h"


enum Orientation : int { vertical = 0, horizontal = 1 };
enum Hit : int { no = 0, touched = 1, killed = 2 };
enum IsShip : int {no_ship = 0, yes = 1};

class Gamer {
protected:
	std::vector<std::vector<int>> field;
	
public:
	//деконструктор
	Gamer() {
		int _size;
		field.resize(10);
		for (int i = 0, _size = field.size(); i < _size; i++) {
			field[i].resize(10);
		}
	}
	virtual std::vector<int> attack(std::vector<std::vector<int>> &my_turns) = 0;
	virtual void init_field() {}

	int is_ship(int x, int y) {
		int left = x, right = x, up=y, down=y;
		if (field[x][y] == IsShip::yes) {
			while (1) {
				if ((left> 0)&&((y+1>9)||(field[left][y+1] == 0))&&((y-1<0)||(field[left][y-1]==0))&&(field[left][y] != 0)) {
					left--;
					if (field[left][y] == IsShip::yes)
						return 1;
			    }
				else {
					if ((right < 9) && ((y+1>9)||(field[right][y + 1] == 0)) && ((y-1<0)||(field[right][y- 1] == 0))&&(field[right][y] != 0)) {
						right++;
						if (field[right][y] == IsShip::yes)
							return 1;
					}
					else {
						if ((down> 0) && ((x+1>9)||(field[x+1][down] == 0)) && ((x-1<0)||(field[x-1][down] == 0))&& (field[x][down] != 0)) {
							down--;
							if (field[x][down] == IsShip::yes)
								return 1;
						}
						else {
							if ((up < 9) && ((x + 1 > 9) || (field[x + 1][up] == 0)) && ((x - 1 < 0) || (field[x - 1][up] == 0))&& (field[x][up] != 0)) {
								up++;
								if (field[x][up] == IsShip::yes)
									return 1;
							}
							else
								return 2;
						}
					}
				}
			}
		}
		
		return 0;
	}

	std::vector<std::vector<int>> field_for_draw() {
		return field;
	}

	int num_ships(std::vector<std::vector<int>> my_turns) {
		int count = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (my_turns[i][j] == Hit::killed) //подбит
					count++;
			}
		}

		return count;
	}

	bool can_set(int x, int y, int num_palubs, int orientatation, std::vector<std::vector<int>> _field) {
		int left, right, up, down, shift_x = 1, shift_y = 1;
		if (x == 9) {
			right = x;
		}
		else right = x + 1;
		if (y == 0) {
			down = y;
		}
		else down = y - 1;

		if (orientatation ==Orientation::horizontal)
			shift_x = num_palubs;
		else shift_y = num_palubs;

		if ((x > 9) || (y > 9) || (x < 0) || (y < 0))
			return 1;
		if ((x - shift_x + 1) < 0)
			return 1;
		if ((y + shift_y - 1) > 9)
			return 1;

		if ((x - shift_x + 1) == 0) {
			left = x - shift_x + 1;
		}
		else left = x - shift_x;

		if ((y + shift_y - 1) == 9) {
			up = y + shift_y - 1;
		}
		else
			up = y + shift_y;
		for (int i = left; i <= right; i++) {
			for (int j = down; j <= up; j++) {
				if (_field[i][j] != Hit::no)
					return 1;
			}
		}
		return 0;
	}

	~Gamer() {
		for (int i = 0; i < field.size(); i++) {
			field[i].clear();
		}
		field.clear();
	}

};

class OptimalGamer : public Gamer {
	std::vector<int> palubs;
	int cur_x = 3, cur_y = 0;
	
	std::list<std::list<int>> free_place(int field_orientation, int side, int pal) {
		std::list<std::list<int>> free_cells;
		int up, down, left, right;
		if(field_orientation == Orientation::horizontal) {
			up = 9;
			down = 0;
			if (side) {
				left = 6;
				right = 9;
			}
			else {
				left = 0;
				right = 3;
			}
		}
		else {
			left = 0;
			right = 9;
			if (side) {
				up = 6;
				down = 9;
			}
			else {
				up = 0;
				down = 3;
			}
		}

		std::list<int> place;
		for (int i = left; i <= right; i++) {
			for (int j = up; j <= down; j++) {
				if (!(can_set(i+1, j, pal, Orientation::horizontal, field))) {
					place.clear();
					place.push_back(i);
					place.push_back(j);
					place.push_back(Orientation::horizontal);
					free_cells.push_back(place);
				}
				if (!(can_set(i, j, pal, Orientation::vertical, field))) {
					place.clear();
					place.push_back(i);
					place.push_back(j);
					place.push_back(Orientation::vertical);
					free_cells.push_back(place);
				}
			}
		}
		return free_cells;
	}


public:
	std::vector<int> attack(std::vector<std::vector<int>> &my_turns) {
	
		int res = 0, orientation = 1;
		//while (!res) {
			if (my_turns[cur_x][cur_y] == Hit::killed) {
			  	
			}
			else {
				//if (my_turns[cur_x][cur_y] == Hit::no) {
					std::vector<int> set_this;
					set_this.resize(2);
					int pal, k=0;
					while (palubs[k] != 0)
						pal = 4 - k;
					cur_x += pal % 10;
					cur_y += pal / 10;
					while (my_turns[cur_x][cur_y] != Hit::no) {
						cur_x = (cur_x++) % 10;
						cur_y += (cur_y++) / 10;
					}
					set_this[0] = cur_x;
					set_this[1] = cur_y;
					return set_this;
			//		res = 1;
				}
				
		//	}
		//}
	}

	void init_field() override {
		int orientation = rand() % 2;
		int side, res = 1, x_right, x_left, y_down, y_up;
		
		for (int pal = 4; pal > 2; pal--) {
			for (int ships_count = 0; ships_count < 5 - pal; ships_count++) {
				while (res) {
					side = rand() % 2;
					orientation = rand() % 2;
					//side = 0;
					//orientation = 0;
					if (orientation == Orientation::horizontal) {
						x_right = rand() % 10;
						x_left = x_right - pal + 1;
						if (side) {
							y_down = 9;
							y_up = 9;
						}
						else {
							y_down = 0;
							y_up = 0;
						}
					}
					else {
						y_down = rand() % 10;
						y_up = y_down + pal - 1;
						if (side) { 
							x_right = 9;
							x_left = 9;
						}
						else {
							x_right = 0;
							x_left = 0;
						}
					}
					res = can_set(x_right, y_down, pal, orientation, field);
				}
				for (int i = x_left; i <= x_right; i++) {
					for (int j = y_down; j <= y_up; j++)
						field[i][j] = 1;
				}
				res = 1;
			}
		}

		orientation = rand() % 2;
		side = rand() % 2;
		std::list<std::list<int>> free_cells;
		int x, y, ship_orientation;

		for (int i = 0; i < 3; i++) {
			free_cells = free_place(orientation, side, 2);
			if (free_cells.size() != 0) {
				const int _size = free_cells.size();
				int ind = rand() % _size;
				auto cur_cells = free_cells.begin();
				while (ind > 0) {
					++cur_cells;
					ind--;
				}
				auto cur = (*cur_cells).begin();
				x = *cur;
				++cur;
				y = *cur;
				++cur;
				ship_orientation = *cur;

			}
			else {
				int res = 1;
				while (res) {
					x = rand() % 10;
					y = rand() % 10;
					ship_orientation = rand() % 2;
					res = can_set(x, y, 2, ship_orientation, field);
				}
				free_cells.clear();
			}

			field[x][y] = IsShip::yes;
			if (orientation == 1)
				x--;
			else
				y++;
			field[x][y] = 1;
		}

		for (int i = 0; i < 4; i++) {
			int x = rand() % 10;
			int y = rand() % 10;
			if (!(res = can_set(x, y, 1, Orientation::horizontal, field)))
				field[x][y] = IsShip::yes;
		}

	}
};

class ConsoleGamer : public Gamer {
public:
	std::vector<int> attack(std::vector<std::vector<int>> &my_turns) {
		int x, y;
		std::cin >> x;
		std::cin >> y;

		std::vector<int> set_this;
		set_this.resize(2);
		set_this[0] = x;
		set_this[1] = y;
		return set_this;
	}

	void init_field() override {
		int x, y;
		int orientation, res = 1;

		for (int i = 1; i < 5; i++) {
			for (int j = 5 - i; i > 0; i++) {
				while (res) {
					std::cin >> x;
					std::cin >> y;
					std::cin >> orientation;
					res = can_set(x, y, i, orientation, field);
				}
				field[x][y] = IsShip::yes;
			}
		}
	}
};

class random_stragegyGamer : public Gamer {


public:
	std::vector<int> attack(std::vector<std::vector<int>> &my_turns) {
		int res = 1, x, y;
		srand(time(0));

		while (res) {
			x = rand() % 10;
			y = rand() % 10;
			res = my_turns[x][y];
		}

		std::vector<int> set_this;
		set_this.resize(2);
		set_this[0] = x;
		set_this[1] = y;
		return set_this;
	}

	void init_field() override {
		int res = 1, x, y, orientation, shift_x = 1, shift_y = 1, j, k, m;

		for (k = 1; k <= 4; k++) {
			for (int i = 0; i < 5 - k; i++) {
				while (res) {
					x = rand() % 10;
					y = rand() % 10;
					orientation = rand() % 2;
					res = can_set(x, y, k, orientation, field);
				}
				if (orientation) {
					shift_x = x - k + 1;
					shift_y = y;
				}
				else {
					shift_y = y + k - 1;
					shift_x = x;
				}
				for (m = shift_x; m <= x; m++) {
					for (j = y; j <= shift_y; j++) {
						field[m][j] = 1;
					}
				}
				res = 1;
			}
		}
	}
};

#endif