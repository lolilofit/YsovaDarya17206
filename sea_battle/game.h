#ifndef PARSE_H
#define PARSE_H

#include<vector>
#include <ctime>
#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<string.h>
#include"optionparser.h"
#include "console_view.h"
#include "arena.h"



class Game {
	std::vector<int> win = { 0, 0 };
	void kill(int &_gamer, Gamer* enemy, std::vector<int> set_this, Arena* game_field) {
	
		if (enemy->field[set_this[0]][set_this[1]] == 1) {
			game_field->hit(_gamer, set_this, 2);
			_gamer++;
		}
		else {
			game_field->hit(_gamer, set_this, 1);
		}
	}
public:
	void game(Gamer* first, Gamer* second, int raunds) {
		
		ConsoleView painter;
		Arena* game_field;
		game_field = new Arena();

		for (int i = 1; i <= raunds; i++) {
			int res = 0, count = 0;
			while (res == 0) {
				std::vector<int> set_this;
				if (count % 2 == 0) {
					painter.draw("attack!", first->field, game_field->turns_one);
					set_this = game_field->turn(count, first);
					kill(count, second, set_this, game_field);
				}
				else {
					painter.draw("attack!", second->field, game_field->turns_two);
					set_this = game_field->turn(count, second);
					kill(count, first, set_this, game_field);
				}
				count++;
				res = game_field->num_ships();
			}
			if (res == 1)
				win[0]++;
			else
				win[1]++;
		}
	
		delete[] game_field;
	}



};


#endif // !parse
