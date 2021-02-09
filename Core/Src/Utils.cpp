#include "pch.h"

#include "Utils.h"

#include <stdexcept>

void OmniliumKnox::Core::Utils::GetWorkingDirectory(LPWSTR lpDest) {
	if (wcslen(lpDest) < MAX_PATH) {
		throw std::invalid_argument("lpDest length < MAX_PATH");
	}

	GetModuleFileName(NULL, lpDest, MAX_PATH);
}