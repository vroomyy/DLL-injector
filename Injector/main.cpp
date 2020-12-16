#include "Includes.hpp"
#include "wrapper.hpp"
#include "Injector.hpp"

int main(int argc, char* argv[])
{
    SetConsoleTitleA("Vroom's DLL injector lol");

    if (vroom::get_dll_path().empty()) // Makes sure you have a dll in your path
    {
        std::cout << "Make sure you have vroom.dll in your folder.\n";
        std::cin.get();
        exit(-1);
    }

    if (argc == 2) // Makes sure you have dragged something into the injector
    {
        if (!vroom::EndsWith(argv[1], ".exe")) // Makes sure you have dragged a .exe into the injector
        {
            std::cout << "Please drag the .exe into the injector.\n";
            std::cin.get();
            exit(-1);
        }

        DWORD pid = vroom::start_program(argv[1]);

        if(pid)
        {
            HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
            std::string dll_path = vroom::get_dll_path();
            Injector::InjectDLL(hProc, dll_path.c_str());
        }
    }
    else
    {
        std::cout << "Drag'n drop!\n";
        std::cin.get();
        exit(-1);
    }
}