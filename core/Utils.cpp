#include "private/pch.h"

#include "Utils.h"

#include <stdexcept>

using namespace knox::core;

void Utils::GetWorkingDirectory(LPWSTR destination)
{
	if (wcslen(destination) > MAX_PATH) {
		throw std::invalid_argument("lpDest length > MAX_PATH");
	}

	GetModuleFileName(nullptr, destination, MAX_PATH);
}

BOOL Utils::DirectoryExists(LPCWSTR path)
{
	DWORD file_attributes = GetFileAttributes(path);

	return (file_attributes != INVALID_FILE_ATTRIBUTES && (file_attributes & FILE_ATTRIBUTE_DIRECTORY));
}

HMODULE Utils::GetCurrentModule()
{
	HMODULE module = nullptr;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)&GetCurrentModule, &module);

	return module;
}

void Utils::SetApplicationIcon(HWND window, DWORD icon)
{
	HANDLE large_icon = LoadImage(
			GetCurrentModule(),
					MAKEINTRESOURCE(icon),
			IMAGE_ICON,
			GetSystemMetrics(SM_CXICON),
			GetSystemMetrics(SM_CYICON),
			0
	);

	if (large_icon) {
		SendMessage(window, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(large_icon));
	}

	HANDLE small_icon = LoadImage(
			GetCurrentModule(),
					MAKEINTRESOURCE(icon),
			IMAGE_ICON,
			GetSystemMetrics(SM_CXSMICON),
			GetSystemMetrics(SM_CYSMICON),
			0
	);

	if (small_icon) {
		SendMessage(window, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(small_icon));
	}
}