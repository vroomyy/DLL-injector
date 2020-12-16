#include "Includes.hpp"
#include "Injector.hpp"

namespace Injector {

	void InjectDLL(HANDLE hProc, const char* dll_path)
	{
		if (hProc != INVALID_HANDLE_VALUE)
		{
			// very simple

			void* location = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			WriteProcessMemory(hProc, location, dll_path, strlen(dll_path) + 1, 0);
			HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, location, 0, 0);

			CloseHandle(hThread);
			CloseHandle(hProc);


			exit(-12); // close the injector (optional)
		}
	}
}