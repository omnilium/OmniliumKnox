#include "private/pch.h"

#include "Logging.h"
#include "Utils.h"

#include <iostream>

using namespace knox::core;
using std::make_unique;
using std::lock_guard;

mutex Logging::_log_mutex = mutex();

Logging::Logging()
{
	if (! Utils::DirectoryExists(L".\\logs\\")) {
		CreateDirectory(L".\\logs\\", nullptr);
	}

	_log_file = CreateFile(L".\\logs\\log.txt", FILE_APPEND_DATA, 0, nullptr, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, nullptr);

	if (_log_file == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		this->Log(LOG_LEVEL_WARN, L"Error creating log file: %lu\n", error);

		_log_file_valid = false;
	}

	_start_time = GetTickCount64();
}

Logging& Logging::GetInstance()
{
	static Logging instance;
	return instance;
}

BOOL Logging::IsReady() const
{
	return _start_time > 0;
}

BOOL Logging::IsFileReady() const
{
	return _log_file_valid;
}

void Logging::Log(DWORD log_level, LPCWSTR format, ...)
{
	LPCWSTR log_level_char = L" ";
	switch (log_level) {
	case LOG_LEVEL_TRACE: log_level_char = L"T";
		break;
	case LOG_LEVEL_DEBUG: log_level_char = L"D";
		break;
	default:
	case LOG_LEVEL_INFO: log_level_char = L"I";
		break;
	case LOG_LEVEL_WARN: log_level_char = L"W";
		break;
	case LOG_LEVEL_ERROR: log_level_char = L"E";
		break;
	}

	if (! IsReady()) {
		return;
	}

	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	ULONGLONG timestamp = GetTickCount64() - _start_time;

	va_list args;
			va_start(args, format);
	WCHAR formatted_message[LOG_MAX_MESSAGE_LENGTH];
	vswprintf_s(formatted_message, LOG_MAX_MESSAGE_LENGTH, format, args);
			va_end(args);

	WCHAR message[LOG_MAX_ENTRY_LENGTH];
	swprintf_s(message,
			LOG_MAX_ENTRY_LENGTH,
			L"[%s][%08I64d][%d][%d] %s\n",
			log_level_char,
			timestamp,
			pid,
			tid,
			formatted_message);

	wprintf_s(L"%s", message);

	if (! IsFileReady()) {
		return;
	}

	lock_guard<mutex> lock(_log_mutex);

	if (! WriteFile(_log_file, message, lstrlenW(message) * sizeof(wchar_t), nullptr, nullptr)) {
		_log_file_valid = false;

		DWORD error = GetLastError();
		Log(LOG_LEVEL_WARN, L"Error writing log file: 0x%08x\n", error);

		return;
	}
}
