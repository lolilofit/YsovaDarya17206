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
#include"optionparser.h"

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
	virtual void attack(std::vector<std::vector<int>> &my_turns, Gamer _gamer) {}
	virtual void init_field() {}

	bool is_ship(int x, int y) {
		return field[x][y];
	}

	std::vector<std::vector<int>> field_for_draw() {
		return field;
	}

	int num_ships(std::vector<std::vector<int>> my_turns) {
		int count = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (my_turns[i][j] == 2) //подбит
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

		if (orientatation == 1)
			shift_x = num_palubs;
		else shift_y = num_palubs;

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
				if ((_field[i][j] == 1) || (_field[i][j] == 2))
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
	int palubs = 4;
	int cur_x = 3, cur_y = 0;
	bool place_in_half(int orientation,  int side, int pal) {
		int shift_x, sift_y;
		if(orientation)
		for (int i = side + 5; i>side+pal-1; i--)
	
	}

public:
	void attack(std::vector<std::vector<int>> &my_turns, Gamer _gamer) override {
	
		int res = 0, orientation = 1;
		while (!res) {
			if (my_turns[cur_x][cur_y] == 2) {
				for (int i = 1; i <= palubs; i++) {
					if ((cur_x - 1 >= 0) && (my_turns[cur_x - 1][cur_y] == 0))
						cur_x--;
					else {
						if ((cur_x + 1 <= 9) && (my_turns[cur_x + 1][cur_y] == 0))
							cur_x++;
						else
						{
							if ((cur_y - 1 >= 0) && (my_turns[cur_x][cur_y - 1] == 0))
								cur_y--;
							else
							{
								if ((cur_y + 1 <= 9) && (my_turns[cur_x][cur_y + 1] == 0))
									cur_y++;
							}
						}
					}
				}
			}
			else {
				if (my_turns[cur_x][cur_y] == 0) {
					if (_gamer.is_ship(cur_x, cur_y) == 1)
						my_turns[cur_x][cur_y] = 2;
					else
						my_turns[cur_x][cur_y] = 1;
					res = 1;
				}
				else {
					if ((cur_y + (cur_x + palubs) / 10) == 10) {
						palubs -= 1;
						cur_x = 0;
						cur_y = 0;
					}
					cur_y += (cur_x + palubs) / 10;
					cur_x += cur_x % 10;
				}
			}
		}
	}

	void init_field() override {
		int orientation = rand() % 2;
		int side, res = 1, x_right, x_left, y_down, y_up;
		//if (side)
		//	side = 4;
		//else side = 0;
		for (int pal = 4; pal > 2; pal--) {
			for (int cnt = 0; cnt < 5 - pal; cnt++) {
				while (res) {
					side = rand() % 2;
					if (orientation) {
						x_right = rand() % 10;
						x_left = x_right - pal + 1;
						if (side) { y_down = 9; y_up = 9; }
						else {
							y_down = 0; y_up = 0;
						}
					}
					else {
						y_down = rand() % 10;
						y_up = y_down + pal - 1;
						if (side) { x_right = 9; x_left = 9; }
						else { x_right = 0; x_left - 0; }
					}
					res = can_set(x_right, y_down, orientation, 4, field);
				}
				for (int i = x_left; i <= x_right; i++) {
					for (int j = y_down; j <= y_up; j++)
						field[i][j] = 1;
				}
				res = 1;
			}
		}
		if (side)
			side = 4;
		else side = 0;

	}
};

class ConsoleGamer : public Gamer {
public:
	void attack(std::vector<std::vector<int>> &my_turns, Gamer _gamer) override {
		int x, y;
		std::cin >> x;
		std::cin >> y;
		if (_gamer.is_ship(x, y))
			my_turns[x][y] = 2;
		else
			my_turns[x][y] = 1;
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
				field[x][y] = 1;
			}
		}
	}
};

class random_stragegyGamer : public Gamer {


public:
	void attack(std::vector<std::vector<int>> &my_turns, Gamer _gamer) override {
		int res = 1, x, y;
		srand(time(0));

		while (res) {
			x = rand() % 10;
			y = rand() % 10;
			res = my_turns[x][y];
		}
		if (_gamer.is_ship(x, y))
			my_turns[x][y] = 2;
		else
			my_turns[x][y] = 1;

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