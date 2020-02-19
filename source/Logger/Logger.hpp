#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>
# include <vector>
# include <sstream>
# include <fstream>
# include <iostream>
// type check for StreamCollection
# include <type_traits>
// unique_ptr, make_unique
# include <memory>
// time related structure & functions
# include <chrono>
// file & folder check
# include <sys/types.h>
# include <sys/stat.h>


/* namespace Logger
 * A very simple, header-only Logger.
 *
 * level	-> specify how much information we want to log.
 * sinks	-> output streams. see Logger::StreamCollection class.
 * _log()	-> main log function. Please use instead the wrapper LOG().
 */
namespace Logger
{
	// Level: represent the severity of the log
	enum class Level : std::int8_t
	{
		DEBUG = -1,
		INFO = 0,
		WARNING = 1,
		ERROR = 2,
		FATAL = 3
	};
	
	// Helper func for Level type printing
	inline std::ostream	&operator<<(std::ostream &out, Logger::Level value)
	{
		switch (value)
		{
			case Level::DEBUG:
				out << "DEBUG";
				break;
			case Level::INFO:
				out << "INFO";
				break;
			case Level::WARNING:
				out << "WARNING";
				break;
			case Level::ERROR:
				out << "ERROR";
				break;
			case Level::FATAL:
				out << "FATAL";
				break;
		}
		return out;
	}


	// Helper functions for string representation of time
	inline std::string	_getTimeStr()
	{
		auto	now = std::chrono::system_clock::now();
		time_t	time_now = std::chrono::system_clock::to_time_t(now);
		char	buff[64]{};

		std::strftime(buff, sizeof(buff), "%H:%M:%S", localtime(&time_now));
		int ms_part = std::chrono::time_point_cast<std::chrono::milliseconds>(now)
			.time_since_epoch().count() % 1000;
		snprintf(buff + strlen(buff), 5, ".%03d", ms_part);

		return buff;
	}

	// Helper functions for string representation of date
	inline std::string	_getDateStr()
	{
		time_t	now = time(NULL);
		char	buff[64]{};

		std::strftime(buff, sizeof(buff), "%Y-%m-%d", localtime(&now));

		return buff;
	}


	/* namespace LogFile
	 * provide info and functions about the log file.
	 *
	 * name()				-> return the default name of the log file.
	 * getStream(filename)	-> instanciate a ofstream on the requested filename.
	 */
	namespace LogFile
	{
		inline std::string	name()
		{
			struct stat info;

			// check if the logs folder exist
			if (stat("logs/", &info) == 0 && info.st_mode & S_IFDIR)
				return "logs/" + _getDateStr() + ".log";
			else
				return _getDateStr() + ".log";
		}

		inline std::ofstream	getStream(std::string filename = name())
		{
			return std::ofstream(filename, std::ios_base::out | std::ios_base::app);
		}
	};

	/* StreamCollection
	 * This class handle several output streams.
	 * There is 1 default and imutable stream: an ofstream instance, requested from LogFile namespace.
	 *
	 * add()	-> add a stream to the collection.
	 * clear()	-> clear the stream collection (not the LogFile stream instance).
	 * op<<()	-> output a value on each stream.
	 */
	class StreamCollection
	{
	public:
		using Stream = std::unique_ptr<std::ostream>;

		StreamCollection()
		{
			this->add(LogFile::getStream());
		}

		~StreamCollection()
		{
			std::stringstream	ss;
			ss << Logger::_getTimeStr() << " [" << Level::INFO << "] Finish Logging.\n";
			*this << ss.str();
		}

		template <typename StreamT>
		void	add(StreamT &&os)
		{
			using SType = typename std::remove_reference<StreamT>::type;
			static_assert(std::is_base_of<std::ostream, SType>::value, "Can only receive an output stream.");

			if constexpr (std::is_same<std::ostream, SType>::value)// expected to work for cout & cerr
				this->_list.push_back(std::make_unique<std::ostream>(os.rdbuf()));
			else
				this->_list.push_back(std::make_unique<SType>(std::forward<StreamT>(os)));

			std::stringstream	ss;
			ss << Logger::_getTimeStr() << " [" << Level::INFO << "] Start Logging.\n";
			*this->_list.back() << ss.str();
		}

		void	clear()
		{
			std::stringstream	ss;
			ss << Logger::_getTimeStr() << " [" << Level::INFO << "] Finish Logging.\n";
	
			while (this->_list.size() > 1)//don't pop the LogFile stream
			{
				*this->_list.back() << ss.str();
				this->_list.pop_back();
			}
		}

		template <typename T>
		StreamCollection &operator<<(T &&value)
		{
			for (auto &stream : this->_list)
				*stream << value;

			return *this;
		}

	private:
		std::vector<Stream>	_list;
	};


	// Variables
	inline StreamCollection	sinks;
	inline Level			level{};


	// Main log function implementation
	template <typename ... PackT>
	void	_log(Level lvl, PackT ... msg)
	{
		std::stringstream	ss;
		if (lvl < Logger::level)
			return ;

		ss << Logger::_getTimeStr();
		ss << " [" << lvl << "] ";
		(ss << ... << msg) << std::endl;

		sinks << ss.str();
		if (lvl == Level::FATAL)
			exit(1);
	}
};

// Type Alias for readability
using LogLevel = Logger::Level;

// LOG(): a convenient wrapper for the main log function.
template <typename ... PackT>
void	LOG(LogLevel lvl, PackT ... msg)
{
	Logger::_log(lvl, msg...);
}

#endif // LOGGER_HPP