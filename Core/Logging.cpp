#include "pch.h"
#include "Logging.h"

#include <iostream>

OmniliumKnox::Core::Logging* OmniliumKnox::Core::Logging::_spInstance = NULL;
HANDLE OmniliumKnox::Core::Logging::_shMutex = NULL;
ULONGLONG OmniliumKnox::Core::Logging::_sullStartTime = 0;

OmniliumKnox::Core::Logging::Logging() {
	_sullStartTime = GetTickCount64();
}

OmniliumKnox::Core::Logging::~Logging() {
	if (_shMutex != NULL) {
		CloseHandle(_shMutex);
	}

	if (_spInstance != NULL) {
		delete _spInstance;
	}
}

OmniliumKnox::Core::Logging* OmniliumKnox::Core::Logging::GetInstance() {
	if (_shMutex == NULL) {
		// TODO: Create private namespace for objects and place the Mutex there.
		_shMutex = CreateMutex(0, FALSE, L"OmniliumKnox.Core.Logging.Logging.Mutex");

		if (_shMutex == NULL) {
			// TODO: Mutex could not be created, handle.
			return NULL;
		}
	}

	DWORD dwWaitResult = WaitForSingleObject(_shMutex, INFINITE);

	if (dwWaitResult == WAIT_ABANDONED) {
		// TODO: Mutex is abandoned, possible corrupted state, handle.
		return NULL;
	}

	if (_spInstance == NULL) {
		_spInstance = new Logging();
	}

	ReleaseMutex(_shMutex);

	return _spInstance;
}

void OmniliumKnox::Core::Logging::Log(DWORD dwLogLevel, LPCWSTR lpFormat, ...) {
	WCHAR wcErrorLevel[1];
	switch (dwLogLevel) {
	case LOG_LEVEL_TRACE:
		wcErrorLevel[0] = L'T';
		break;
	case LOG_LEVEL_DEBUG:
		wcErrorLevel[0] = L'D';
		break;
	case LOG_LEVEL_INFO:
		wcErrorLevel[0] = L'I';
		break;
	case LOG_LEVEL_WARN:
		wcErrorLevel[0] = L'W';
		break;
	case LOG_LEVEL_ERROR:
		wcErrorLevel[0] = L'E';
		break;
	}

	DWORD dwPid = GetCurrentProcessId();
	DWORD dwTid = GetCurrentThreadId();
	ULONGLONG ullTimestamp = GetTickCount64() - _sullStartTime;

	va_list args;
	va_start(args, lpFormat);
	WCHAR wcFormat[LOG_MAX_MESSAGE_LENGTH];
	vswprintf_s(wcFormat, LOG_MAX_MESSAGE_LENGTH, lpFormat, args);
	va_end(args);

	WCHAR wcMessage[LOG_MAX_ENTRY_LENGTH];
	swprintf_s(wcMessage, LOG_MAX_ENTRY_LENGTH, L"[%I64d][%d][%d] %s\n", ullTimestamp, dwPid, dwTid, wcFormat);

	wprintf_s(L"%s", wcMessage);

	// TODO: Add logging to file.
}