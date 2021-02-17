#include "private/pch.h"

#include "Utils.h"

#include <stdexcept>

void knox::core::Utils::GetWorkingDirectory(LPWSTR lpDest) {
	if (wcslen(lpDest) < MAX_PATH) {
		throw std::invalid_argument("lpDest length < MAX_PATH");
	}

	GetModuleFileName(nullptr, lpDest, MAX_PATH);
}

BOOL knox::core::Utils::DirectoryExists(LPCWSTR lpPath) {
	DWORD dwAttrib = GetFileAttributes(lpPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

HMODULE knox::core::Utils::GetCurrentModule() {
	HMODULE hModule = nullptr;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)&GetCurrentModule, &hModule);

	return hModule;
}
