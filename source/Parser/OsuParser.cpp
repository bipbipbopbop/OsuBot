#include <regex>
#include <algorithm>
#include <iostream>

#include "Logger.hpp"
#include "OsuParser.hpp"
#include "OsuKey.hpp"


OsuParser::OsuParser(std::string filename)
	: _filename(std::move(filename)), _fileVersion(0), _isParsed(false)
{
	if (this->_filename != "")
		this->parse();
}


bool					OsuParser::isParsed(void) const
{
	return this->_isParsed;
}

bool					OsuParser::parse(std::string filename)
{
	std::ifstream	fstream;

	if (filename != "")
		this->_filename = filename;	
	if (this->_filename == "")
	{
		LOG(LogLevel::WARNING, "OsuParser: no file provided ; no parsing performed.");
		return false;
	}

	// reset what has already been parsed
	this->_fileContent = OsuParser::SectionList();
	this->_fileVersion = 0;

	fstream.open(this->_filename);
	if (!fstream.is_open() && fstream.fail())
	{
		LOG(LogLevel::ERROR, "OsuParser: can't open \"", this->_filename, '\"');
		return false;
	}

	this->_isParsed = this->_internal_parse(fstream);
	fstream.close();
	return this->_isParsed;
}

bool					OsuParser::_internal_parse(std::ifstream &fstream)
{
	std::string			currentLine;
	const std::regex	versionRegex("^osu file format v([0-9]+)\r?$");
	const std::regex	sectionRegex("\\[([a-zA-Z]+)\\]\r?$");
	const std::regex	keyRegex("(?:([a-zA-Z0-9]+)\\s?:\\s?)?(.+)\r?$");
	const std::regex	commentRegex("^//.*\r?$");
	std::smatch			regexResult;
	std::string			currentSection;
	size_t				ValueIndex = 0;// Used when no key is provided

	// Check if the file is a .osu file
	if (!std::getline(fstream, currentLine) || !std::regex_match(currentLine, regexResult, versionRegex))
	{
		LOG(LogLevel::WARNING, "OsuParser: \"", this->_filename, "\" is not a valid .osu file.");
		return false;
	}
	else
		this->_fileVersion = std::stoi(regexResult[1].str());
	while (std::getline(fstream, currentLine))
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


std::string				OsuParser::getVal(const std::string &sectName, const OsuParser::Key key) const
{
	try
	{
		return this->_fileContent.at(sectName).at(key);
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


OsuParser::SectionList::const_iterator	OsuParser::cbegin() const noexcept
{
	return this->_fileContent.cbegin();
}

OsuParser::SectionList::const_iterator	OsuParser::cend() const noexcept
{
	return this->_fileContent.cend();
}


void					OsuParser::dump(void) const
{
	if (this->_fileVersion <= 0)
	{
		std::cerr << "Invalid file ; no dump performed.\n";
		return ;
	}
	else
		std::cout << "osu file format v" << this->_fileVersion << std::endl << std::endl;
	for (auto &sect : this->_fileContent)
	{
		std::cout << "[" << sect.first << "]\n";
		std::for_each(sect.second.begin(), sect.second.end(), [](decltype(sect.second)::value_type elem){
			std::cout << "(" << elem.first << "): " << elem.second << std::endl;
		});
		std::cout << std::endl << std::endl;
	}
}
