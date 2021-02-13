#pragma once

#include "Core.h"

namespace OmniliumKnox {
	namespace Core {
		class CORE_API Utils {
		public:
			static void GetWorkingDirectory(LPWSTR lpDest);
			static BOOL DirectoryExists(LPCWSTR);
			static HMODULE GetCurrentModule();
		};
	}
};
