#include "private/pch.h"

#include "Logging.h"
#include "Utils.h"
#include "private/version.h"

#include <iostream>

using namespace knox::core;

int main()
{
    Utils::SetApplicationIcon(GetConsoleWindow(), APP_ICON);
    SetWindowText(GetConsoleWindow(), L"Omnilium Knox");

    Logging* pLogging = Logging::GetInstance();

    pLogging->Log(LOG_LEVEL_INFO, L"Loading KnoxCLI v%s (file v%s)", PRODUCT_VERSION, FILE_VERSION);

    system("pause");
}
