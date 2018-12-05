#include "gamer.h"


Gamer::Gamer() {
	int _size;
	field.resize(10);
	for (int i = 0, _size = field.size(); i < _size; i++) {
		field[i].resize(10);
	}
}

bool Gamer::can_set(int x, int y, int num_palubs, int orientatation, std::vector<std::vector<int>> _field) {
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

Gamer::~Gamer() {
	for (int i = 0; i < field.size(); i++) {
		field[i].clear();
	}
	field.clear();
}


