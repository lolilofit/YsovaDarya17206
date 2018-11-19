#include<iostream>
#include "game.h"
#include "create.h"

bool init_map() {
	random_gamerCreate* _random = new random_gamerCreate();
	ConsoleGamer_Create* _console = new ConsoleGamer_Create();
	RationalGamer_Create* _rational = new RationalGamer_Create();
	factory::get_instance().init_gamer("random", _random);
	factory::get_instance().init_gamer("console", _console);
	factory::get_instance().init_gamer("optimal", _rational);
	return 1;
}


int main(int argc, const char *argv[]) {
	//string
	bool k = init_map();
	Game _session;
	_session.game(argc, argv);
	return 0;
}