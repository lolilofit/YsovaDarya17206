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


static void printError(const char* msg1, const option::Option& opt, const char* msg2)
{
	fprintf(stderr, "ERROR: %s", msg1);
	fwrite(opt.name, opt.namelen, 1, stderr);
	fprintf(stderr, "%s", msg2);
}
static option::ArgStatus Players(const option::Option& option, bool msg)
{
	if ((strcmp(option.arg, "=random") == 0) || (strcmp(option.arg, "=console") == 0) || (strcmp(option.arg, "=optimal") == 0))
		return option::ARG_OK;

	if (msg)
		printError("Option '", option, "' requires an argument\n");
	return option::ARG_ILLEGAL;
}

static option::ArgStatus Number(const option::Option& option, bool msg)
{
	std::string str = option.arg;
	for (int i = 1; i < str.size(); i++)
	{
		if ((option.arg[i] < '0') || (option.arg[i] > '9')) {
			if (msg)
				printError("Option '", option, "' requires an argument\n");
			return option::ARG_ILLEGAL;
		}
	}
	return option::ARG_OK;
}



enum  optionIndex { HELP, COUNT, FIRST, SECOND };
const option::Descriptor usage[] =
{
	{ HELP, 0, "h" , "help", option::Arg::None, "" },
{ COUNT, 0, "c" , "count", Number, "" },
{ FIRST, 0, "f" , "first", Players, "" },
{ SECOND, 0, "s" , "second", Players, "" }
};

void pars(int argc, const char *argv[], int &raunds, std::string &name_one, std::string &name_two) {
	argc -= (argc>0); argv += (argc>0);
	option::Stats  stats(usage, argc, argv);
	std::vector<option::Option> options(stats.options_max);
	std::vector<option::Option> buffer(stats.buffer_max);
	option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

	if (parse.error())
		return;
	if (options[HELP]) {
		ConsoleView _help;
		_help.help();
		return;
	}

	if (options[FIRST]) {
		option::Option* opt = options[FIRST];
		name_one = std::string(opt->arg).erase(0, 1);
	}
	if (options[SECOND]) {
		option::Option* opt = options[SECOND];
		name_two = std::string(opt->arg).erase(0, 1);

	}
	if (options[COUNT]) {
		option::Option* opt = options[COUNT];
		raunds = stoi(std::string(opt->arg).erase(0, 1));
	}
}

int main(int argc, const char *argv[]) {
	int raunds = 1;
	std::string name_one = "random", name_two = "random";
	bool k = init_map();

	Gamer* first;
	Gamer* second;
	srand(time(0));
	pars(argc, argv, raunds, name_one, name_two);
	first = factory::get_instance().read(name_one)->make();
	first->init_field();
	second = factory::get_instance().read(name_two)->make();
	second->init_field();

	Game _session;
	_session.game(first, second, raunds);
	return 0;
}
