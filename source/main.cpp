#include <string>
#include <iostream>

#include "jhache/Logger.hpp"
#include "Parser/OsuParser.hpp"

#ifdef HAS_CONFIG_FILE
# include "OsuBotConfig.h"
#endif// HAS_CONFIG_FILE

void	usage(char *progName)
{
		std::cout << "OsuBot: A bot that play Osu for you!" << std::endl;
#ifdef OSUBOT_CONFIG_H
		std::cout << "\tVersion " << VERSION << std::endl;
#endif// OSUBOT_CONFIG_H
		std::cout << std::endl << "Usage: " << progName << " <filename>" << std::endl;
		return ;
}

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		usage(av[0]);
		return 0;
	}

	const std::string	filename(av[1]);
	OsuParser			parser;

	LOG(LogLevel::INFO, "Parsing ", filename);
	parser.parse(filename);
	LOG(LogLevel::INFO, "dumping ", filename);
	parser.dump();

	return 0;
}
