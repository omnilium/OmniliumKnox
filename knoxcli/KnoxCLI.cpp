#include "private/pch.h"

#include "Logging.h"

#include "private/Resources.h"

#include <iostream>

using namespace OmniliumKnox::Core;

int main() {
	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(APP_ICON));
	SendMessage(GetConsoleWindow(), WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
	SendMessage(GetConsoleWindow(), WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
	SetWindowText(GetConsoleWindow(), L"Omnilium Knox");

	Logging* pLogging = Logging::GetInstance();

	pLogging->Log(LOG_LEVEL_INFO, L"Application startup");

	system("pause");
}
