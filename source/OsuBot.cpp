#include "OsuBot.hpp"

#include "jhack.hpp"
#include "Logger.hpp"

OsuBot::OsuBot()
{
	;
}

bool		OsuBot::attachProcess()
{
	HANDLE	processHandle;

	processHandle = jhack::getProcessHandleByName(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, _T("osu!.exe"));
	if (processHandle == NULL)
	{
		char	ErrorStr[512];

		LOG(LogLevel::Error, "OsuBot: received a NULL handle while retrieving osu! process handle.");
		FormatMessageA(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				ErrorStr,
				sizeof(ErrorStr),
				NULL);
		LOG(LogLevel::Debug, "GetLastError: ", ErrorStr);
		return false;
	}
	this->_finder.setProcessHandle(processHandle);
	if (processHandle == INVALID_HANDLE_VALUE)
	{
		LOG(LogLevel::Info, "OsuBot: no Osu! process found.");
		return false;
	}
	return true;
}

bool		OsuBot::checkProcess() const
{
	return this->_finder.isHandleValid();
}

std::string	OsuBot::getCurrentMap()
{
	HWND		OsuWHandle;
	char		windowTitle[512];
	std::string	wtStr;

	OsuWHandle = jhack::findWindowhandleByName("osu!");
	if (OsuWHandle == NULL)
	{
		char	ErrorStr[512];

		LOG(LogLevel::Error, "OsuBot: received a NULL handle while retrieving osu! process window handle.");
		FormatMessageA(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				ErrorStr,
				sizeof(ErrorStr),
				NULL);
		LOG(LogLevel::Debug, "GetLastError: ", ErrorStr);
		return "";
	}

	GetWindowTextA(OsuWHandle, windowTitle, 512);
	wtStr = windowTitle;

	if (wtStr.find("osu!  - ") == 0)
		return (wtStr.substr(8, wtStr.find('[') - 9));
	else
	{
		LOG(LogLevel::Info, "OsuBot: No map currently playing.");
		return "";
	}
}