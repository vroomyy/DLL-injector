#include "Includes.hpp"
#include "wrapper.hpp"

DWORD vroom::GetProcID(const char* procname)
{
	DWORD pid = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pEntry;
		pEntry.dwSize = sizeof(pEntry);

		if (Process32First(snapshot, &pEntry))
		{
			do 
			{
				if (!strcmp(pEntry.szExeFile, procname))
				{
					pid = pEntry.th32ProcessID;
					break;
				}

			} while (Process32Next(snapshot, &pEntry));
		}
	}

	return pid;
}

std::string vroom::GetFileName(const char* path)
{
	std::string filename = path;

	const size_t last_slash_idx = filename.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		filename.erase(0, last_slash_idx + 1);
	}

	return filename;
}

bool vroom::EndsWith(std::string string, std::string ending)
{
	if (string.length() >= ending.length()) {
		return (0 == string.compare(string.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

std::string vroom::get_dll_path() 
{
	std::string dll_path;

	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	std::string path(buff);

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (vroom::EndsWith(entry.path().u8string(), "vroom.dll"))
		{
			dll_path = entry.path().u8string().c_str();
			break;
		}
	}
	return dll_path;
}
DWORD vroom::start_program(LPCSTR lpApplicationName)
{
	DWORD pid;
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcessA
	(
		lpApplicationName,   
		(LPSTR)lpApplicationName,
		NULL,                
		NULL,                
		FALSE,               
		CREATE_NEW_CONSOLE,  
		NULL,       
		NULL,       
		&si,        
		&pi         
	);
	pid = pi.dwProcessId;

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return pid;
}