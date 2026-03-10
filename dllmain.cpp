// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <cstdio>
#include <iostream>
#include "Core.h";
#include "Hooks.h"
#include "Logger.h"


using namespace std;

namespace Core {
    uintptr_t moduleBase = 0x00400000;
}

void CreateConsole()
{
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);
    HWND hwndConsole = GetConsoleWindow();
    ShowWindow(hwndConsole, SW_SHOW);
    std::cout << "AP Mod initialized!" << std::endl;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        try {
            CreateConsole();
            Logger::Get().Start();
            Logger::Get().Log("First");
            MH_Uninitialize();
            MH_Initialize();
            Hooks::SetupHooks();
            MH_EnableHook(MH_ALL_HOOKS);
        }
        catch (exception ex) {
            cerr << GetLastError();
        }
        break;
    case DLL_THREAD_ATTACH:

        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        FreeConsole();
        break;
    }
    return TRUE;
}



