#include <string>
#include <iostream>
#include <type_traits>

#include "Logger.hpp"
#include "Parser/OsuParser.hpp"
#include "OsuBotTestsConfig.h"

bool	test1(OsuParser &parser)
{
	bool	res = true;

	if (std::is_copy_constructible<OsuParser>::value
		|| std::is_copy_assignable<OsuParser>::value)
		res &= false;

	OsuParser	dummy;
	{
		dummy.parse("/wrongfile");
		std::string	filename = dummy.getFilename();
		OsuParser	movedParser(std::move(dummy));
		if (movedParser.isParsed()
			|| movedParser.getFilename() != filename
			|| movedParser.cbegin() != movedParser.cend())
		{
			LOG(LogLevel::ERROR, "error in OsuParser move op");
			res &= false;
		}
	}

	return res;
}

bool	test2(OsuParser &parser)
{
	bool	res = true;
	std::string	defaultPath(std::string(DataPath) + "/Default");
	OsuParser	defaultMap(defaultPath);

	if (!defaultMap.isParsed()
		|| defaultMap.getFilename() != defaultPath
		|| defaultMap.cbegin() == defaultMap.cend())
	{
		LOG(LogLevel::ERROR, "error while parsing \"", defaultPath, "\".");
		res &= false;
	}

	if (defaultMap.getSection("General") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("Metadata") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("Difficulty") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("Events") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("TimingPoints") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("HitObjects") == defaultMap.getSection("FakeSection"))
	{
		LOG(LogLevel::ERROR, "Incomplete file parsing for beatmap \"", defaultPath, "\".");
		res &= false;
	}

	const OsuParser::Section &general = defaultMap.getSection("General");
	const OsuParser::Section &meta = defaultMap.getSection("Metadata");
	if (defaultMap.getVal("General", std::string("AudioFilename")) == ""
		|| defaultMap.getVal("Metadata", std::string("Title")) == "")
	{
		LOG(LogLevel::ERROR, "Incomplete sections parsing for beatmap \"", defaultPath, "\".");
		res &= false;
	}

	return res;
}

bool	test3(OsuParser &parser)
{
	bool	res = true;

	// Parse specific .osu file(s) and search for hardcoded specific keys

	return res;
}

int		main(int ac, char **av)
{
	OsuParser	parser;
	bool		OK = true;
	Logger::level = LogLevel::DEBUG;
	Logger::sinks.add(std::cout);

	LOG(LogLevel::INFO, "##### OsuParser Class Tests #####");
	
	LOG(LogLevel::INFO, "\tImplementation behavior & I/O testing...");
	OK &= test1(parser);
	LOG(LogLevel::INFO, "\tDone\n");

	LOG(LogLevel::INFO, "\tBasic testing...");
	OK &= test2(parser);
	LOG(LogLevel::INFO, "\tDone");

	LOG(LogLevel::INFO, "\tAdvanced testing...");
	OK &= test3(parser);
	LOG(LogLevel::INFO, "\tDone");

	LOG(LogLevel::INFO, "Result of the test (see log file): ", (OK ? "Success!" : "Error"));
	LOG(LogLevel::INFO, "#################################");
	return 0;
}
