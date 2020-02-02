#include <regex>
#include <algorithm>
#include <iostream>

#include "OsuParser.hpp"
#include "OsuKey.hpp"


OsuParser::OsuParser(const std::string &filename)
	: _filename(filename)
{
	this->parse();
}


bool					OsuParser::isParsed(void) const
{
	return !(this->_filename == "" || this->_fileContent.empty());
}

bool					OsuParser::parse(std::string filename)
{
	if (filename != "")
		this->_filename = filename;

	// reset what has already been parsed
	this->_fileContent = OsuParser::SectionList();

	this->_fstream.open(this->_filename);
	if (!this->_fstream.is_open() && this->_fstream.fail())
	{
		this->_log += "Error: can't open \"" + this->_filename + "\"\n";
		return false;
	}

	bool	res = this->_internal_parse();
	this->_fstream.close();
	return res;
}

bool					OsuParser::_internal_parse(void)
{
	std::string			currentLine;
	const std::regex	sectionRegex("\\[([a-zA-Z]+)\\]\r$");
	const std::regex	keyRegex("(?:([a-zA-Z0-9]+)\\s?:\\s?)?(.+)\r$");
	const std::regex	commentRegex("^//.*\r$");
	std::smatch			regexResult;
	std::string			currentSection;
	size_t				ValueIndex = 0;// Used when no key is provided

	// Check if the file is a .osu file
	if (!std::getline(this->_fstream, currentLine) || currentLine.find("osu file format") == std::string::npos)
	{
		this->_log += "Error: \"" + this->_filename + "\" is not a valid .osu file.\n";
		return false;
	}
	while (std::getline(this->_fstream, currentLine))
	{
		if (std::regex_match(currentLine, commentRegex))
		{// it's a Comment
			;// skip
		}
		else if (std::regex_match(currentLine, regexResult, sectionRegex))
		{// it's a Section title
			currentSection = regexResult[1].str();
			//ValueIndex = 0;// May cause problems if a malformated file contains twice the same section
		}
		else if (std::regex_match(currentLine, regexResult, keyRegex))
		{// it's a Value
			OsuParser::Key	key;
			if (regexResult[1].str() == "")
				key = ValueIndex++;
			else
				key = regexResult[1].str();

			this->_fileContent[currentSection][key] = regexResult[2].str();
		}
	}
	return true;
}


std::string				OsuParser::getVal(const std::string &sectName, const std::string &keyName) const
{
	try
	{
		return this->_fileContent.at(sectName).at(keyName);
	}
	catch (std::out_of_range &e)
	{
		return "";
	}
}

const OsuParser::Section	&OsuParser::getSection(const std::string &sectName) const
{
	static const OsuParser::Section	dummy;

	try
	{
		return this->_fileContent.at(sectName);
	}
	catch (std::out_of_range &e)
	{
		return dummy;
	}
}


std::string				OsuParser::getFilename(void) const
{
	return this->_filename;
}

std::string				OsuParser::log(void)
{
	return std::move(this->_log);
}

void					OsuParser::dump(void) const
{
	for (auto &sect : this->_fileContent)
	{
		std::cout << "[" << sect.first << "]\n";
		std::for_each(sect.second.begin(), sect.second.end(), [](decltype(sect.second)::value_type elem){
			std::cout << "(" << elem.first << "): " << elem.second << std::endl;
		});
		std::cout << std::endl << std::endl;
	}
}
