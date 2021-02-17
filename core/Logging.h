#pragma once

#include "Core.h"
#include "RAIITemplates.h"

constexpr int LOG_LEVEL_TRACE = 0;
constexpr int LOG_LEVEL_DEBUG = 1;
constexpr int LOG_LEVEL_INFO = 2;
constexpr int LOG_LEVEL_WARN = 3;
constexpr int LOG_LEVEL_ERROR = 4;

constexpr int LOG_MAX_MESSAGE_LENGTH = 400;
constexpr int LOG_MAX_ENTRY_LENGTH = 500;

namespace knox::core {
    class CORE_API Logging {
    private:
        static Logging* _spInstance;
        static ULONGLONG _sullStartTime;

        AutoHandle<HANDLE>* _hLogFile = nullptr;

    protected:
        Logging();

        ~Logging();

    public:
        Logging(Logging& other) = delete;

        void operator=(const Logging&) = delete;

        static Logging* GetInstance();

        void Log(DWORD dwLogLevel, LPCWSTR lpFormat, ...);
    };
};
