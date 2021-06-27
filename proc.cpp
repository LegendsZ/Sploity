#include "proc.h"

DWORD getProcessID(const wchar_t* name) {
	DWORD processID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);
		if (Process32First(hSnap, &entry)) {
			do {
				if (!_wcsicmp(name, entry.szExeFile)) {
					processID = entry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &entry));
		}
	}
	CloseHandle(hSnap);
	return processID;
}

uintptr_t getModBaseAddy(DWORD processID, const wchar_t* name) {
	uintptr_t baseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);

	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 entry;
		entry.dwSize = sizeof(entry);
		if (Module32First(hSnap, &entry)) {
			do {
				if (!_wcsicmp(name, entry.szModule)) {
					baseAddress = (uintptr_t)entry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &entry));
		}
	}
	CloseHandle(hSnap);
	return baseAddress;
}

uintptr_t findDMAAddy(HANDLE hProcess, uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addy = ptr + offsets[0];

	for (unsigned int i = 1; i < offsets.size(); i++) { //try ++i if no work
		ReadProcessMemory(hProcess, (BYTE*)addy, &addy, sizeof(addy), nullptr);
		addy += offsets[i];
	}
	return addy;
}