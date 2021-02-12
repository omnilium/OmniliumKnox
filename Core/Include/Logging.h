#pragma once

#include "Core.h"
#include "RAIITemplates.h"

#define LOG_LEVEL_TRACE 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO  2
#define LOG_LEVEL_WARN  3
#define LOG_LEVEL_ERROR 4

#define LOG_MAX_MESSAGE_LENGTH 400
#define LOG_MAX_ENTRY_LENGTH   500

namespace OmniliumKnox {
	namespace Core {
		class CORE_API Logging {

		private:
			static Logging* _spInstance;
			static ULONGLONG _sullStartTime;

			AutoHandle<HANDLE>* _hLogFile = NULL;

		protected:
			Logging();
			~Logging();

		public:
			Logging(Logging& other) = delete;
			void operator=(const Logging&) = delete;

			static Logging* GetInstance();

			void Log(DWORD dwLogLevel, LPCWSTR lpFormat, ...);
		};
	}
};
