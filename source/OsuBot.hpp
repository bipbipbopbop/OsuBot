#ifndef OSUBOT_HPP
# define OSUBOT_HPP

# include <string>

# include "Finder/OsuFinder.hpp"
# include "Parser/OsuParser.hpp"

class OsuBot
{
public:
	OsuBot();

	/*
	 * attachProcess():
	 * Try to find a running 'osu!.exe' process, and retrieve its handle (internally).
	 */
	bool		attachProcess();
	/*
	 * checkProcess():
	 * Return true if the currently attached process correspond to a running 'osu!.exe' process.
	 */
	bool		checkProcess() const;

	/*
	 * getCurrentMap():
	 * Return the name of the currently playing map, if there is one.
	 * Return an empty string otherwise.
	 */
	static std::string	getCurrentMap();

private:
	OsuParser	_parser;
	OsuFinder	_finder;
};

#endif // OSUBOT_HPP