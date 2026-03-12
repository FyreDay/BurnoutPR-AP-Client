#pragma once
#include "MinHook.h"
#include "Events.h"
#include "Core.h"
#include <cstdint>
#include <iostream>
#include "ItemHandler.h"

class Hooks
{
private:
	static void __stdcall EventHook();
	static void __stdcall Breakhook();
	static void __stdcall IslandBreakhook();
	static void __stdcall ShowEventHook();

public:
	
	static void SetupHooks();
};