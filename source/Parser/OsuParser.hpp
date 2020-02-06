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

	OsuParser(std::string filename = "");
	OsuParser(const OsuParser &) = delete;
	OsuParser(OsuParser &&) = default;
	~OsuParser(void) = default;
	OsuParser &operator=(const OsuParser &) = delete;
	OsuParser &operator=(OsuParser &&) = default;

	bool			isParsed(void) const;
	bool			parse(std::string filename = "");// empty string == parse the current file.

	std::string		getVal(const std::string &sectName, const Key key) const;
	const Section	&getSection(const std::string &sectName) const;
	std::string		getFilename(void) const;

	// debug
	std::string		log(void);
	void			dump(void) const;

private:
	bool			_internal_parse(std::ifstream &fstream);

	std::string		_filename;
	SectionList		_fileContent;
	int				_fileVersion;
	std::string		_log;
	bool			_isParsed;
};


#endif // OSUPARSER_HPP