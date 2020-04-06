#include <filesystem>

#include "OsuFinder.hpp"
#include "Logger.hpp"
#include "jhack.hpp"


Finder::Finder()
	: _processHandle(INVALID_HANDLE_VALUE)
{}

Finder::Finder(HANDLE processHandle)
{
	this->setProcessHandle(processHandle);
}


bool		Finder::isHandleValid() const
{
	return this->_processHandle != INVALID_HANDLE_VALUE;
}

void		Finder::setProcessHandle(HANDLE processHandle)
{
	if (processHandle == INVALID_HANDLE_VALUE)
		LOG(LogLevel::Warning, "Finder: received an invalid handle value.");
	else if (processHandle == NULL)
	{
		char	ErrorStr[512];

		LOG(LogLevel::Error,
			"Finder: received a NULL handle, calling GetLastError() ...\n",
			FormatMessageA(
					FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					ErrorStr,
					sizeof(ErrorStr),
					NULL));
		return;
	}

	this->_processHandle = processHandle;
	this->_processDirectory = jhack::getProcessPath(this->_processHandle).string();
}

HANDLE		Finder::getProcessHandle() const
{
	return this->_processHandle;
}

std::string	Finder::getprocessDir() const
{
	return this->_processDirectory;
}



OsuFinder::OsuFinder()
	: Finder::Finder(jhack::getProcessHandleByName(PROCESS_VM_READ, _T("osu!.exe")))
{}

std::string	OsuFinder::findMap(std::string mapName) const
{
	const std::filesystem::path	osuPath(this->_processDirectory + "/Songs");
	
	for (auto &entry : std::filesystem::directory_iterator(osuPath))
	{
		const std::string	fileName = entry.path().filename().string();

		if (fileName.find(mapName) != std::string::npos)
			return entry.path().string();
	}
	return "";
}
