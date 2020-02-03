#include <string>
#include <iostream>
#include <type_traits>

#include "Parser/OsuParser.hpp"

bool	test1(OsuParser &parser)
{
	bool	res = true;

	// Class cpp feature (cpy/move op, ...)

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
