#include <string>
#include <iostream>

#include "Logger.hpp"
#include "jhack.hpp"
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

	jhack::start();

	const std::string	filename(av[1]);
	OsuParser			parser;

	LOG(LogLevel::Info, "Parsing ", filename);
	parser.parse(filename);
	LOG(LogLevel::Info, "dumping ", filename);
	parser.dump();

	return 0;
}
