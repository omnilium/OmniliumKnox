#pragma once

#include "Core.h"

namespace knox::core {
class CORE_API Utils {
public:
	static void GetWorkingDirectory(LPWSTR destination);

	static BOOL DirectoryExists(LPCWSTR);

	static HMODULE GetCurrentModule();

	static void SetApplicationIcon(HWND window, DWORD icon);
};
};
