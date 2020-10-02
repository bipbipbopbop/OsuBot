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
	DWORD	exitCodeProcess;

	if (!GetExitCodeProcess(this->_processHandle, &exitCodeProcess))
		return false;
	return (this->_processHandle != INVALID_HANDLE_VALUE
			&& exitCodeProcess == STILL_ACTIVE);//jhack::testProcessHandle(this->_processHandle));
}

void		Finder::setProcessHandle(HANDLE processHandle)
{
	if (processHandle == INVALID_HANDLE_VALUE)
		LOG(LogLevel::Warning, "Finder: received an invalid handle value.");
	else if (processHandle == NULL)
	{
		LOG(LogLevel::Warning, "Finder: received a NULL handle.");
		return;
	}

	this->_processHandle = processHandle;
	this->_processDirectory = jhack::getProcessPath(this->_processHandle).string();
	if (processHandle != INVALID_HANDLE_VALUE && this->_processDirectory == "")
	{
		char	ErrorStr[512];

		LOG(LogLevel::Error, "OsuFinder: Error while retrieving the executable path.");
		FormatMessageA(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				ErrorStr,
				sizeof(ErrorStr),
				NULL);
		LOG(LogLevel::Debug, "GetLastError: ", ErrorStr);
	}
}

HANDLE		Finder::getProcessHandle() const
{
	return this->_processHandle;
}

std::string	Finder::getProcessDir() const
{
	return this->_processDirectory;
}



OsuFinder::OsuFinder()
	: Finder::Finder()
{}

OsuFinder::OsuFinder(HANDLE OsuProcesshandle)
	: Finder::Finder(OsuProcesshandle)
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
