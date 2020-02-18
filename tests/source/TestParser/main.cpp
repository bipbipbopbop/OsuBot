#include <string>
#include <iostream>
#include <type_traits>

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
			|| movedParser.log().size() == 0
			|| movedParser.getFilename() != filename
			|| movedParser.cbegin() != movedParser.cend())
		{
			std::cout << "Error in move op" << std::endl;
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
		std::string	log = defaultMap.log();

		if (log.size() == 0)
			log = "Undetected error while parsing \"" + defaultPath + "\".";
		std::cout << log << std::endl;
		res &= false;
	}

	if (defaultMap.getSection("General") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("Metadata") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("Difficulty") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("Events") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("TimingPoints") == defaultMap.getSection("FakeSection")
		|| defaultMap.getSection("HitObjects") == defaultMap.getSection("FakeSection"))
	{
		std::cout << "Error: Incomplete file parsing for beatmap \"" << defaultPath + "\"." << std::endl;
		res &= false;
	}

	const OsuParser::Section &general = defaultMap.getSection("General");
	const OsuParser::Section &meta = defaultMap.getSection("Metadata");
	if (defaultMap.getVal("General", std::string("AudioFilename")) == ""
		|| defaultMap.getVal("Metadata", std::string("Title")) == "")
	{
		std::cout << "Error: Incomplete sections parsing for beatmap \"" << defaultPath + "\"." << std::endl;
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

	std::cout << "##### OsuParser Class Tests #####\n\n";
	
	std::cout << "\tImplementation behavior & I/O testing...\t";
	OK &= test1(parser);
	std::cout << "Done\n";

	std::cout << "\tBasic testing...\t\t\t\t";
	OK &= test2(parser);
	std::cout << "Done\n";

	std::cout << "\tAdvanced testing...\t\t\t\t";
	OK &= test3(parser);
	std::cout << "Done\n";

	std::cout << "\nResult of the test (see log file): " << (OK ? "Success!" : "Error") << std::endl;
	std::cout << "#################################\n";
	return 0;
}
