#ifndef CREATE_H
#define CREATE_H

#include"gamer.h"

class Create {
public:
	virtual Gamer* make() = 0 {}
};

class random_gamerCreate : public Create {
	Gamer* make() {
		return new random_stragegyGamer();
	}
};

class ConsoleGamer_Create : public Create {
	Gamer* make() {
		return new ConsoleGamer();
	}
};

class RationalGamer_Create : public Create {
	Gamer* make() {
		return new OptimalGamer();
	}
};

class factory {
	std::map<std::string, Create*> gamers;
public:
	static factory& get_instance() {
		static factory _factory;
		return _factory;
	}

	void init_gamer(std::string name, Create* _gamer) {
		gamers[name] = _gamer;
	}

	Create* read(std::string name) {
		return gamers.at(name);
	}
};


#endif // !CREATE_H
