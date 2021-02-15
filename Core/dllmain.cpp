#include "private/pch.h"

#include "Logging.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	OmniliumKnox::Core::Logging* pLogging = OmniliumKnox::Core::Logging::GetInstance();

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		pLogging->Log(LOG_LEVEL_DEBUG, L"Core attached.");
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		pLogging->Log(LOG_LEVEL_DEBUG, L"Core detached.");
		break;
	}
	return TRUE;
}
