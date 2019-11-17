#include <string>
#include <iostream>

#include "Parser/OsuParser.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./OsuBot <filename>" << std::endl;
		return 0;
	}

	const std::string	filename(av[1]);
	OsuParser			parser;

	std::cout << "Parsing " << filename << std::endl;
	parser.parse(filename);
	std::cout << "dumping " << filename << std::endl;
	parser.dump();

	return 0;
}
