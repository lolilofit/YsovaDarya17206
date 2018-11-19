//#pragma once
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

class Game {
	std::vector<int> win = { 0, 0 };
public:
	void game(int argc, const char *argv[]) {
		int raunds = 1;
		std::string name_one = "random", name_two = "random", name;

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

		Arena game_field(name_one, name_two);
		for (int i = 1; i <= raunds; i++) {
			int res = game_field.num_ships(), count = 0;
			while (res == 0) {
				game_field.turn(count);
				count++;
				res = game_field.num_ships();
			}
			if (res == 1)
				win[0]++;
			else
				win[1]++;
		}
	}



};


#endif // !parse

