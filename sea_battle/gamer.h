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
	Gamer() {
		int _size;
		field.resize(10);
		for (int i = 0, _size = field.size(); i < _size; i++) {
			field[i].resize(10);
		}
	}
	virtual std::vector<int> attack(std::vector<std::vector<int>> &my_turns) = 0;
	virtual void init_field() {}
	
	
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

		if (orientatation == Orientation::horizontal)
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
	int cur_x = 3, cur_y = 0, cur_ship_x = 3, cur_ship_y = 0, ship_left = cur_x - 1, ship_right = cur_x + 1, ship_down = cur_y - 1, ship_up = cur_y + 1;
	int mistake(int x, int y) {
		if ((x >= 0) && (x <= 9) && (y >= 0) && (y <= 9))
			return 0;
		else
			return 1;
	}

	std::list<std::list<int>> free_place(int field_orientation, int side, int pal) {
		std::list<std::list<int>> free_cells;
		int up, down, left, right;
		if (field_orientation == Orientation::horizontal) {
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
		for (int i = left + 1; i <= right; i++) {
			for (int j = up + 1; j <= down; j++) {
				if (!(can_set(i + 1, j, 2, Orientation::horizontal, field))) {
					place.clear();
					place.push_back(i);
					place.push_back(j);
					place.push_back(Orientation::horizontal);
					free_cells.push_back(place);
				}
				if (!(can_set(i, j, 2, Orientation::vertical, field))) {
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
	
	void next_turn(int pal, std::vector<std::vector<int>> &my_turns) {

		int k = 0;
		int h = std::max(ship_right - ship_left - 1, ship_up - ship_down - 1);
		palubs[4 - std::max(ship_right - ship_left - 1, ship_up - ship_down - 1)]++;

		if (std::max(ship_right - ship_left - 1, ship_up - ship_down - 1) == pal) {
			while ((palubs.at(k) == k + 1) && (k<4)) {
				k++;
				pal = 4 - k;
			}
			pal = 4 - k;

			cur_x = pal - 1;
			cur_y = 0;
			mistake(cur_x, cur_y);
			while (my_turns[cur_x][cur_y] != Hit::no) {
				cur_y += (cur_x + pal) / 10;
				if (pal != 1)
					cur_x = (!((cur_x + pal) / 10))*(cur_x + pal) + ((cur_x + pal) / 10)*(pal - 1 - cur_y % pal);
				else
					cur_x = (cur_x + 1) % 10;
				mistake(cur_x, cur_y);
			}
		}
		else {
			cur_y += (cur_x + pal) / 10;
			if (pal != 1)
				cur_x = (!((cur_x + pal) / 10))*(cur_x + pal) + ((cur_x + pal) / 10)*(pal - 1 - cur_y % pal);
			else
				cur_x = (cur_x + 1) % 10;
			mistake(cur_x, cur_y);
			while (my_turns[cur_x][cur_y] != Hit::no) {
				cur_y += (cur_x + pal) / 10;
				if (pal != 1)
					cur_x = (!((cur_x + pal) / 10))*(cur_x + pal) + ((cur_x + pal) / 10)*(pal - 1 - cur_y % pal);
				else
					cur_x = (cur_x + 1) % 10;
				mistake(cur_x, cur_y);
			}
		}
		cur_ship_x = cur_x;
		cur_ship_y = cur_y;
		ship_down = cur_ship_y - 1;
		ship_up = cur_ship_y + 1;
		ship_down = cur_ship_x - 1;
		ship_right = cur_ship_x + 1;

	}

public:
	std::vector<int> attack(std::vector<std::vector<int>> &my_turns) {
		int pal = 4, k = 0;
		std::vector<int> set_this;
		set_this.resize(4);

		palubs.resize(4);

		while ((palubs.at(k) == k + 1) && (k<4)) {
			k++;
			pal = 4 - k;
		}
		pal = 4 - k;


		if (my_turns[cur_ship_x][cur_ship_y] == Hit::killed) {
			if (cur_ship_x != cur_x) {
				if (cur_ship_y - 1 >= 0)
					my_turns[cur_ship_x][cur_ship_y - 1] = 1;
				if (cur_ship_y + 1 <= 9)
					my_turns[cur_ship_x][cur_ship_y + 1] = 1;
			}
			if (cur_ship_y != cur_y) {
				if (cur_ship_x - 1 >= 0)
					my_turns[cur_ship_x - 1][cur_ship_y] = 1;
				if (cur_ship_x + 1 <= 9)
					my_turns[cur_ship_x + 1][cur_ship_y] = 1;
			}

			if ((cur_ship_x - 1 >= 0) && (my_turns[cur_ship_x - 1][cur_ship_y] == Hit::no))
				cur_ship_x--;
			else {
				if (((cur_ship_x - 1 < 0) || (my_turns[cur_ship_x - 1][cur_ship_y] == Hit::touched)) && (cur_y == cur_ship_y)) {

					ship_left = cur_ship_x - 1;
					if (cur_x + 1 <= 9)
						cur_ship_x = cur_x + 1;
					else {
						ship_right = 10;
						cur_ship_x = cur_x;
						if (cur_ship_y - 1 >= 0)
							cur_ship_y--;
						else {
							ship_down = cur_y - 1;
							if (cur_ship_y + 1 <= 9)
								cur_ship_y++;
							else {
								ship_up = cur_ship_y + 1;
								next_turn(pal, my_turns);
							}
						}
					}
				}
				else {
					if ((cur_ship_x + 1 <= 9) && (my_turns[cur_ship_x + 1][cur_ship_y] == Hit::no))
						cur_ship_x++;
					else {
						if (((cur_ship_x + 1 > 9) || (my_turns[cur_ship_x + 1][cur_ship_y] == Hit::touched)) && (cur_ship_y == cur_y)) {

							ship_right = cur_ship_x + 1;
							cur_ship_x = cur_x;
							if (cur_ship_y - 1 >= 0)
								cur_ship_y--;
							else {
								ship_down = cur_y - 1;
								if(cur_ship_y+1 <= 9)
								 cur_ship_y++;
								else {
									ship_up = cur_ship_y + 1;
									next_turn(pal, my_turns);
								}
							}
						}
						else {
							if ((cur_ship_y - 1 >= 0) && (my_turns[cur_ship_x][cur_ship_y - 1] == Hit::no))
								cur_ship_y--;
							else {
								if (((cur_ship_y - 1 < 0) || (my_turns[cur_ship_x][cur_ship_y - 1] == Hit::touched)) && (cur_x == cur_ship_x)) {
									ship_down = cur_ship_y - 1;
									if(cur_ship_y + 1 <= 9)
									 cur_ship_y = cur_y + 1;
									else {
										ship_up = cur_ship_y + 1;
										next_turn(pal, my_turns);
									}
								}
								else {
									if ((cur_ship_y + 1 <= 9) && (my_turns[cur_ship_x][cur_ship_y + 1] == Hit::no))
										cur_ship_y++;
									else {

										ship_up = cur_ship_y + 1;
										next_turn(pal, my_turns);
									}
								}
							}
						}
					}
				}
			}
		}
		else {
			if ((cur_x == cur_ship_x) && (cur_ship_y == cur_y)) {

				mistake(cur_x, cur_y);
				if (my_turns[pal - 1][0] == 1) {
					cur_y += (cur_x + pal) / 10;
					if (pal != 1)
						cur_x = (!((cur_x + pal) / 10))*(cur_x + pal) + ((cur_x + pal) / 10)*(pal - 1 - cur_y % pal);
					else
						cur_x = (cur_x + 1) % 10;
				}
				mistake(cur_x, cur_y);
				while (my_turns[cur_x][cur_y] != Hit::no) {
					cur_y += (cur_x + pal) / 10;
					if (pal != 1)
						cur_x = (!((cur_x + pal) / 10))*(cur_x + pal) + ((cur_x + pal) / 10)*(pal - 1 - cur_y % pal);
					else
						cur_x = (cur_x + 1) % 10;
					mistake(cur_x, cur_y);
				}
				cur_ship_x = cur_x;
				cur_ship_y = cur_y;
				set_this[0] = cur_x;
				set_this[1] = cur_y;
				return set_this;
			}
			else {
				if (cur_ship_x < cur_x) {
					if (cur_ship_y - 1 >= 0)
						my_turns[cur_ship_x][cur_ship_y - 1] = Hit::touched;
					if (cur_ship_y + 1 <= 9)
						my_turns[cur_ship_x][cur_ship_y + 1] = Hit::touched;

					ship_left = cur_ship_x;
					if (cur_x + 1 <= 9)
						cur_ship_x = cur_x + 1;
					else {
						if (cur_ship_y - 1 >= 0) {
							cur_ship_x = cur_x;
							cur_ship_y--;
						}
						else {
							cur_ship_x = cur_x;
							cur_ship_y + 1;
						}
					}
				}
				else {
					if (cur_ship_x > cur_x) {
						if (cur_ship_y - 1 >= 0)
							my_turns[cur_ship_x][cur_ship_y - 1] = Hit::touched;
						if (cur_ship_y + 1 <= 9)
							my_turns[cur_ship_x][cur_ship_y + 1] = Hit::touched;

						ship_right = cur_ship_x;
						cur_ship_x = cur_x;

						if (cur_ship_y - 1 >= 0)
							cur_ship_y--;
						else {
							ship_down = cur_y - 1;
							if (cur_ship_y + 1 <= 9)
								cur_ship_y++;
							else {
								ship_up = cur_ship_y + 1;
								next_turn(pal, my_turns);
							}
						}

						set_this[0] = cur_ship_x;
						set_this[1] = cur_ship_y;
						return set_this;
					}
					else {
						if (cur_ship_y < cur_y) {
							if (cur_ship_x - 1 >= 0)
								my_turns[cur_ship_x - 1][cur_ship_y] = Hit::touched;
							if (cur_ship_x + 1 <= 9)
								my_turns[cur_ship_x + 1][cur_ship_y] = Hit::touched;

							ship_down = cur_ship_y;
							if (cur_y + 1 <= 9)
								cur_ship_y = cur_y + 1;
							else {
								ship_up = 10;
								next_turn(pal, my_turns);
							}
						}
						else {

							if (cur_ship_x - 1 >= 0)
								my_turns[cur_ship_x - 1][cur_ship_y] = Hit::touched;
							if (cur_ship_x + 1 <= 9)
								my_turns[cur_ship_x + 1][cur_ship_y] = Hit::touched;

							ship_up = cur_ship_y;
							next_turn(pal, my_turns);

						}

					}

				}
			}
		}

		set_this[0] = cur_ship_x;
		set_this[1] = cur_ship_y;
		return set_this;
	}

	

	void init_field() override {
		int orientation = rand() % 2;
		int side, res = 1, x_right, x_left, y_down, y_up;


		for (int pal = 4; pal > 2; pal--) {
			for (int ships_count = 0; ships_count < 5 - pal; ships_count++) {
				while (res) {
					side = rand() % 2;
					orientation = rand() % 2;

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
				int _res = 1;
				while (_res) {
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
					_res = mistake(x, y);
				}
			}
			else {
				int res = 1;
				while ((res) || (x - 1<0) || (x>9) || (y<0) || (y + 1>9)) {
					x = rand() % 10;
					y = rand() % 10;
					ship_orientation = rand() % 2;
					res = can_set(x, y, 2, ship_orientation, field);
				}
				free_cells.clear();
			}


			field[x][y] = 1;
			if (orientation == 1)
				x--;
			else
				y++;
			field[x][y] = 1;
		}

		for (int i = 0; i < 4; i++) {
			int _res = 1;
			int x = rand() % 10;
			int y = rand() % 10;
			while (can_set(x, y, 1, Orientation::horizontal, field)) {
				x = rand() % 10;
				y = rand() % 10;
			}
			field[x][y] = 1;
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
