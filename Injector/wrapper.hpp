#include "Includes.hpp"

namespace vroom {
	extern DWORD GetProcID(const char* procname); // We are not using this
	extern std::string GetFileName(const char* path);
	extern bool EndsWith(std::string string, std::string ending);
	extern std::string get_dll_path();

	extern DWORD start_program(LPCSTR lpApplicationName); // -> https://stackoverflow.com/questions/17703721/how-to-execute-another-exe-from-a-c-program-in-windows

}