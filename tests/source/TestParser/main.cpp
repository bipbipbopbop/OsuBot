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

	OsuParser	dummy(std::string(DataPath) + "/Default");
	if (!dummy.isParsed())
	{
		std::cout << dummy.log() << std::endl;
		res &= false;
	}	

	// no file, wrong file, check getFilename...

	return res;
}

bool	test2(OsuParser &parser)
{
	bool	res = true;

	// Default test file, check get* funcs on error and for common keys

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
