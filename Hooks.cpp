#include "pch.h"
#include "Hooks.h";


typedef void(__stdcall* FunctionType)();

FunctionType hookOrigin = nullptr;
uintptr_t hookOriginReturnAddr;

__declspec(naked) void __stdcall Hooks::EventHook()
{
    __asm
    {
        pushfd
        pushad

        push dword ptr[esi - 0xC]
        push dword ptr[esi - 0x10]
        push esi
        call Events::OnGameEvent
        add esp,0xC
        popad
        popfd
        jmp dword ptr[ecx * 4 + 0xA28E10]
    }
}

FunctionType BreakHookOrigin = nullptr;
uintptr_t BreakHookOriginReturnAddr;

__declspec(naked) void __stdcall Hooks::Breakhook()
{
    __asm
    {
        pushfd
        pushad
        push dword ptr[esi + 4]
        push dword ptr[esi]
        push ecx
        call Events::OnBreak
        add esp, 0xC
        popad
        popfd
        mov edi,[esi]
        mov ebx,[esi+4]
        jmp BreakHookOriginReturnAddr
    }
}

FunctionType IslandBreakHookOrigin = nullptr;
uintptr_t IslandBreakHookOriginReturnAddr;

__declspec(naked) void __stdcall Hooks::IslandBreakhook()
{
    __asm
    {
        pushfd
        pushad
        push eax
        push esi
        push ecx
        call Events::OnBreak
        add esp, 0xC
        popad
        popfd
        mov [ecx + edx * 8], esi
        mov[ecx + edx * 8 + 04], eax
        jmp IslandBreakHookOriginReturnAddr
    }
}


void Hooks::SetupHooks()
{
    Logger::Get().Log(std::to_string(Core::moduleBase));
    char* addr;
    
    hookOriginReturnAddr = 0x00A254DD + 7;
    addr = (char*)(0x00A254DD);
    MH_CreateHook((LPVOID)addr, &EventHook, reinterpret_cast<LPVOID*>(&hookOrigin));

    BreakHookOriginReturnAddr = Core::moduleBase + 0x2DDB735 + 5;
    addr = (char*)(Core::moduleBase + 0x2DDB735);
    MH_CreateHook((LPVOID)addr, &Breakhook, reinterpret_cast<LPVOID*>(&BreakHookOrigin));

    IslandBreakHookOriginReturnAddr = Core::moduleBase + 0x2E1079A + 7;
    addr = (char*)(Core::moduleBase + 0x2E1079A);
    MH_CreateHook((LPVOID)addr, &IslandBreakhook, reinterpret_cast<LPVOID*>(&IslandBreakHookOrigin));
}
