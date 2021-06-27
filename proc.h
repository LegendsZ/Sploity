#pragma once

#include <vector>
#include <windows.h>
#include <TlHelp32.h>

DWORD getProcessID(const wchar_t* name);

uintptr_t getModBaseAddy(DWORD processID, const wchar_t* name);

uintptr_t findDMAAddy(HANDLE hProcess, uintptr_t ptr, std::vector<unsigned int> offsets);
