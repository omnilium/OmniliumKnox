#include "pch.h"

#include "Logging.h"

#include <iostream>

using namespace OmniliumKnox::Core;

int main()
{
    Logging* pLogging = Logging::GetInstance();

    pLogging->Log(LOG_LEVEL_INFO, L"Application startup");

    system("pause");
}
