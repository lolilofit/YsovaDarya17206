#ifndef CONSOLE_VIEW
#define CONSOLE_VIEW

#include<iostream>
#include<vector>
#include<string>

class GameView {
public:
	virtual void help() {}
	virtual void draw(std::string message, std::vector<std::vector<int>> my_field, std::vector<std::vector<int>> my_turns) {}
};

class ConsoleView : public  GameView {
public:
	void help() override {
		std::cout << "Choose the type of gamers: (write -f before the type of a gamer for the first gamer; -s for the second gamer) random, console, optimal" << std::endl;
		std::cout << "In the beginning of the game you shoul set your ships if you choosed console gamer. To set the ship you shoul mark the right top coordinate and orientation of the ship" << std::endl;

	}

	void draw(std::string message, std::vector<std::vector<int>> my_field, std::vector<std::vector<int>> my_turns) override {
		system("cls");
		std::cout << message << std::endl << "my field:" << std::endl;
		for (int i = 0; i < 10; i++) {
			std::cout << "|";
			for (int j = 0; j < 10; j++) {
				std::cout << my_field[i][j] << "|";
			}
			std::cout << '\n' << "";
		}
		std::cout << '\n' << '\n' << "my turns:" << '\n';
		for (int i = 0; i < 10; i++) {
			std::cout << "|";
			for (int j = 0; j < 10; j++) {
				std::cout << my_turns[j][i] << "|";
			}
			std::cout << '\n';
		}
	}
};

#endif // !CONSOLE_VIEW
