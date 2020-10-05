#include <Windows.h>
#include "Finder/OsuFinder.hpp"
#include "OsuBotTestsConfig.h"
#include "Logger.hpp"

bool	test1()
{
	bool	res = true;

	if (!std::is_copy_constructible<OsuFinder>::value
		|| !std::is_copy_assignable<OsuFinder>::value
		|| !std::is_move_constructible<OsuFinder>::value
		|| !std::is_move_assignable<OsuFinder>::value)
		res &= false;

	Finder	dummy(GetCurrentProcess());
	if (dummy.getProcessHandle() != INVALID_HANDLE_VALUE)
		res &= false;
	return res;
}

int		main(void)
{
	bool	OK = true;
	Logger::level = LogLevel::Debug;
	Logger::sinks.add(std::cout);

	LOG(LogLevel::Info, "##### OsuFinder Class Tests #####");
	
	LOG(LogLevel::Info, "\tBasic testing...");
	OK &= test1();
	LOG(LogLevel::Info, "\tDone\n");

	//TODO: test2 with a dummy process, or current process, so we can retrieve his path
	//also, if necessary, add this in OsuBotTestsConfig.h.in :
	//constexpr char FinderExePath[] = "@OsuBot_BINARY_DIR@";

	LOG(LogLevel::Info, "Result of the test (see log file): ", (OK ? "Success!" : "Error"));
	LOG(LogLevel::Info, "#################################");
	return 0;
}