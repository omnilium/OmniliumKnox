#pragma once

#include "Core.h"

namespace OmniliumKnox {
	namespace Core {
		template <typename T>
		class CORE_API AutoHandle {

		public:
			T Handle;

			AutoHandle(T hTarget) : Handle(hTarget) {
				if (Handle == INVALID_HANDLE_VALUE) {
					// TODO: Invalid or uninitialized handle provided, handle.
					return;
				}
			}

			~AutoHandle() {
				if (Handle == INVALID_HANDLE_VALUE) {
					// TODO: Possible data corruption, throw error.
					return;
				}

				CloseHandle(Handle);
			}
		};

		class CORE_API AutoMutex {

		private:
			AutoHandle<HANDLE> _hMutex;

		public:
			AutoMutex(LPCWSTR lpMutexName) : _hMutex(CreateMutex(NULL, FALSE, lpMutexName)) { }

			~AutoMutex() {
				ReleaseMutex(_hMutex.Handle);
				delete &_hMutex;
			}

			DWORD AcquireMutex(DWORD dwWaitLimitMs) {
				return WaitForSingleObject(_hMutex.Handle, dwWaitLimitMs);
			}
		};
	}
}