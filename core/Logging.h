#pragma once

#include "Core.h"

#include <memory>
#include <mutex>
#include <shared_mutex>

constexpr int LOG_LEVEL_TRACE = 0;
constexpr int LOG_LEVEL_DEBUG = 1;
constexpr int LOG_LEVEL_INFO = 2;
constexpr int LOG_LEVEL_WARN = 3;
constexpr int LOG_LEVEL_ERROR = 4;

constexpr int LOG_MAX_MESSAGE_LENGTH = 400;
constexpr int LOG_MAX_ENTRY_LENGTH = 500;

using std::mutex;

namespace knox::core {
class CORE_API Logging {
private:
	static mutex _log_mutex;

	HANDLE _log_file = nullptr;
	BOOL _log_file_valid = true;

	ULONGLONG _start_time = 0;

	Logging();
public:
	Logging(Logging& other) = delete;
	void operator=(const Logging&) = delete;

	static Logging& GetInstance();

	[[nodiscard]] BOOL IsReady() const;
	[[nodiscard]] BOOL IsFileReady() const;
	void Log(DWORD log_level, LPCWSTR format, ...);
};
};
