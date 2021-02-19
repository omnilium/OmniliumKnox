#include "private/pch.h"

#include "Logging.h"
#include "Utils.h"

#include <string>

using namespace knox::core;
using std::make_unique;
using std::lock_guard;

mutex Logging::_log_mutex = mutex();

Logging::Logging()
{
	if (! Utils::DirectoryExists(L".\\logs\\")) {
		CreateDirectory(L".\\logs\\", nullptr);
	}

	try {
		ProcessLogFiles();
	}
	catch (...) {
		Log(LOG_LEVEL_ERROR, L"Error processing log files: 0x%08x", GetLastError());
	}

	_log_file = CreateFile(L".\\logs\\log.txt", FILE_APPEND_DATA, 0, nullptr, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, nullptr);

	if (_log_file == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		Log(LOG_LEVEL_WARN, L"Error creating log file: %lu", error);

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
			L"[%s][%08I64d][%06d][%06d] %s\n",
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
		Log(LOG_LEVEL_WARN, L"Error writing log file: 0x%08x", error);

		return;
	}
}

void Logging::ProcessLogFiles() {
	WCHAR old_name[17] = L".\\logs\\log_0.txt";
	WCHAR new_name[17] = L".\\logs\\log_0.txt";

	for (int i = LOG_FILES_TO_KEEP; i >= 0; i--) {
		if (i > 0) {
			old_name[11] = std::to_wstring(i).c_str()[0];
		} else {
			old_name[10] = L'.';
			old_name[11] = L't';
			old_name[12] = L'x';
			old_name[13] = L't';
			old_name[14] = L'\0';
		}

		new_name[11] = std::to_wstring(i + 1).c_str()[0];

		ProcessLogFile(old_name, new_name, i == 3);
	}
}

void Logging::ProcessLogFile(LPCWSTR old_name, LPCWSTR new_name, BOOL delete_if_found) {
	WIN32_FIND_DATA find_data;
	auto file_handle = FindFirstFile(old_name, &find_data);

	if (file_handle != INVALID_HANDLE_VALUE) {
		FindClose(file_handle);

		if (delete_if_found) {
			DeleteFile(old_name);
			return;
		}

		MoveFile(old_name, new_name);
	}
}