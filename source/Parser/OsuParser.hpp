#ifndef OSUPARSER_HPP
# define OSUPARSER_HPP

# include <map>
# include <string>
# include <fstream>

# include "OsuKey.hpp"

class OsuParser
{
public:
	/* A .osu file is very similar to a .ini file. It is composed of Sections.
	 * A Section is a list of Values. (represented as a std::string).
	 * Values may or may not be represented by a Key (see OsuKey.hpp).
	 */

	using Key			= OsuKey;
	using Section		= std::map<Key, std::string>;
	using SectionList	= std::map<std::string, Section>;

	OsuParser(void) = default;
	OsuParser(const OsuParser &) = default;
	OsuParser(OsuParser &&) = default;
	~OsuParser(void) = default;
	OsuParser &operator=(OsuParser &&) = default;
	OsuParser &operator=(const OsuParser &) = default;

	OsuParser(const std::string &filename);

	bool			isParsed(void) const;
	bool			parse(std::string filename = "");// empty string == parse the current file.

	// getVal() work only for values with a string Key.
	// Since values with no string Key are grouped in the same Section,
	// you should call getSection instead.
	std::string		getVal(const std::string &sectName, const std::string &keyName) const;
	const Section	&getSection(const std::string &sectName) const;
	std::string		getFilename(void) const;

	// debug
	std::string		log(void);
	void			dump(void) const;

private:
	bool			_internal_parse(void);

	std::string		_filename;
	std::ifstream	_fstream;
	SectionList		_fileContent;
	std::string		_log;
};


#endif // OSUPARSER_HPP