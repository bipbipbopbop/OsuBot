#include <string>
#include <iostream>

#include "Parser/OsuParser.hpp"

#ifdef HAS_CONFIG_FILE
# include "OsuBotConfig.h"
#endif// HAS_CONFIG_FILE

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "OsuBot: A bot that play Osu for you!" << std::endl;
#ifdef OSUBOT_CONFIG_H
		std::cout << "\tVersion " << VERSION << std::endl;
#endif// OSUBOT_CONFIG_H
		std::cout << std::endl << "Usage: " << av[0] << " <filename>" << std::endl;
		return 0;
	}

	const std::string	filename(av[1]);
	OsuParser			parser;

	std::cout << "Parsing " << filename << std::endl;
	parser.parse(filename);
	std::cout << "dumping " << filename << std::endl;
	parser.dump();
	std::cout << "log:\n" << parser.log();

	return 0;
}
