#include "private/pch.h"

#include "Utils.h"

#include <stdexcept>

void OmniliumKnox::Core::Utils::GetWorkingDirectory(LPWSTR lpDest) {
	if (wcslen(lpDest) < MAX_PATH) {
		throw std::invalid_argument("lpDest length < MAX_PATH");
	}

	GetModuleFileName(NULL, lpDest, MAX_PATH);
}

BOOL OmniliumKnox::Core::Utils::DirectoryExists(LPCWSTR lpPath) {
	DWORD dwAttrib = GetFileAttributes(lpPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

HMODULE OmniliumKnox::Core::Utils::GetCurrentModule() {
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)GetCurrentModule, &hModule);

	return hModule;
}
