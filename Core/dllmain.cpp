#include "private/pch.h"

#include "Logging.h"
#include "private/version.h"

BOOL APIENTRY DllMain([[maybe_unused]] HMODULE hModule,
	    DWORD  ul_reason_for_call,
        [[maybe_unused]] LPVOID lpReserved
    )
{
	knox::core::Logging* pLogging = knox::core::Logging::GetInstance();

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		pLogging->Log(LOG_LEVEL_DEBUG, L"Attaching Core v%s (file v%s)", PRODUCT_VERSION, FILE_VERSION);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		pLogging->Log(LOG_LEVEL_DEBUG, L"Core detached.");
		break;
	default:
	    throw std::exception("Unknown DllMain reason for call");
	}
	return TRUE;
}
