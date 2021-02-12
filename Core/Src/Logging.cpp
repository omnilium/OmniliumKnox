#include "pch.h"

#include "Logging.h"
#include "RAIITemplates.h"
#include "Utils.h"

#include <iostream>

OmniliumKnox::Core::Logging* OmniliumKnox::Core::Logging::_spInstance = NULL;
ULONGLONG OmniliumKnox::Core::Logging::_sullStartTime = 0;

OmniliumKnox::Core::Logging::Logging() {
	if (!Utils::DirectoryExists(L".\\logs\\")) {
		CreateDirectory(L".\\logs\\", NULL);
	}

	HANDLE hLogFile = CreateFile(L".\\logs\\log.txt", FILE_APPEND_DATA, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hLogFile == INVALID_HANDLE_VALUE) {
		// TODO: Cannot create log file, handle.
		DWORD error = GetLastError();
		printf("Error creating log file: %d\n", error);
	}

	_hLogFile = new AutoHandle<HANDLE>(hLogFile);

	_sullStartTime = GetTickCount64();
}

OmniliumKnox::Core::Logging::~Logging() {
	delete& _hLogFile;
}

OmniliumKnox::Core::Logging* OmniliumKnox::Core::Logging::GetInstance() {
	AutoMutex* mutex = new AutoMutex(L"OmniliumKnox.Core.Logging.Logging.Mutex::Instance");
	DWORD dwWaitResult = mutex->Acquire(INFINITE);

	if (dwWaitResult == WAIT_ABANDONED) {
		// TODO: Mutex is abandoned, possible corrupted state, handle.
		printf("Returned Mutex handle was abandoned.");
		return NULL;
	}

	if (_spInstance == NULL) {
		_spInstance = new Logging();
	}

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

	{
		AutoMutex* mutex = new AutoMutex(L"OmniliumKnox.Core.Logging.Logging.Mutex::Write");
		DWORD dwWaitResult = mutex->Acquire(INFINITE);

		if (dwWaitResult == WAIT_ABANDONED) {
			// TODO: Mutex is abandoned, possible corrupted state, handle.
			printf("Returned Mutex handle was abandoned.");
			return;
		}

		if (!WriteFile(_hLogFile->Handle, wcMessage, lstrlenW(wcMessage) * sizeof(wchar_t), NULL, NULL)) {
			// TODO: Cannot create log file, handle.
			DWORD error = GetLastError();
			printf("Error writing log file: %d\n", error);
		}
	}
}