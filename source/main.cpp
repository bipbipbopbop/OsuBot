#include <string>
#include <iostream>

#include "Logger.hpp"
#include "jhack.hpp"
#include "OsuBot.hpp"

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
	jhack::start();
	Logger::sinks.add(std::cout);
	Logger::level = LogLevel::Debug;

	std::string			mapFilename;
	OsuBot				bot;

	//bind bot to the process
	//  if no process, wait for it to exist
	//print currently playing map
	//  if no map, wait for it to be played
	bot.attachProcess();
	while (bot.checkProcess() == false)
	{
		LOG(LogLevel::Info, "No Osu! process found.");
		bot.attachProcess();
		Sleep(5000);
	}
	LOG(LogLevel::Info, "Osu Process found.");
	LOG(LogLevel::Info, "Waiting for a map to be started...");
	while ((mapFilename = bot.getCurrentMap()) == "")
		Sleep(5000);
	LOG(LogLevel::Info, "a map is currently playing! : \"", mapFilename, "\"");
	return 0;
}
