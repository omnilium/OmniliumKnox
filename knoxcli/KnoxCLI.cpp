#include "private/pch.h"

#include "Logging.h"
#include "private/version.h"

#include <iostream>

using namespace knox::core;

int main()
{
    HICON hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(APP_ICON));
    SendMessage(GetConsoleWindow(), WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
    SendMessage(GetConsoleWindow(), WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
    SetWindowText(GetConsoleWindow(), L"Omnilium Knox");

    Logging* pLogging = Logging::GetInstance();

    pLogging->Log(LOG_LEVEL_INFO, L"Loading KnoxCLI v%s (file v%s)", PRODUCT_VERSION, FILE_VERSION);

    system("pause");
}
