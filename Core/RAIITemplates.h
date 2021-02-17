#pragma once

#include <algorithm>
#include "Core.h"

namespace knox::core {
    template<typename T>
    class CORE_API AutoHandle {
    public:
        T Handle;

        explicit AutoHandle(T hTarget)
                :Handle(hTarget)
        {
            if (Handle==INVALID_HANDLE_VALUE) {
                // TODO: Invalid or uninitialized handle provided, handle.
                return;
            }
        }

        AutoHandle(AutoHandle& other)
        {
            Handle = other.Handle;
        }

        AutoHandle& operator=(const AutoHandle& other)
        {
            Handle = other.Handle;
            return *this;
        }

        ~AutoHandle()
        {
            if (Handle==INVALID_HANDLE_VALUE) {
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
        explicit AutoMutex(LPCWSTR lpMutexName)
                :_hMutex(CreateMutex(nullptr, FALSE, lpMutexName)) { }

        AutoMutex(AutoMutex& other)
                :_hMutex(other._hMutex.Handle) { }

        AutoMutex& operator=(const AutoMutex& other)
        {
            HANDLE hHandle = other._hMutex.Handle;
            _hMutex = *new AutoHandle(hHandle);
            return *this;
        }

        ~AutoMutex()
        {
            ReleaseMutex(_hMutex.Handle);
            delete &_hMutex;
        }

        [[nodiscard]] DWORD Acquire(DWORD dwWaitLimitMs) const
        {
            return WaitForSingleObject(_hMutex.Handle, dwWaitLimitMs);
        }

        void Release() const
        {
            ReleaseMutex(_hMutex.Handle);
        }
    };
}
