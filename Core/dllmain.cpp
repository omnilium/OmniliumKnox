#include "private/pch.h"

#include "Logging.h"
#include "private/version.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	OmniliumKnox::Core::Logging* pLogging = OmniliumKnox::Core::Logging::GetInstance();

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
	}
	return TRUE;
}
