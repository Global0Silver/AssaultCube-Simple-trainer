#pragma once
#include "includes.h"
#include <Windows.h>
#include <vector>


DWORD GetProcessID(const wchar_t* procNAME);

DWORD GetModuleBaseAdresss(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);