#pragma once

#include "Core.h"
#include "RAIITemplates.h"

namespace knox::core {
    class CORE_API MappedFile {
    private:
        AutoHandle<HANDLE> _hFile = AutoHandle<HANDLE>(INVALID_HANDLE_VALUE);
        AutoHandle<HANDLE> _hFileMapping = AutoHandle<HANDLE>(INVALID_HANDLE_VALUE);
        AutoHandle<LPVOID> _hFileMapView = AutoHandle<LPVOID>(NULL);
        AutoMutex _mutex;

    public:
        explicit MappedFile(LPCWSTR lpFilePath)
                :_mutex(lpFilePath)
        {
            _mutex.Acquire(INFINITE);
            _hFile = AutoHandle(CreateFile(lpFilePath, GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL, nullptr));
            _hFileMapping = AutoHandle(CreateFileMapping(_hFile.Handle, nullptr, PAGE_READWRITE, 0, 1 << 20,
                    lpFilePath));
            _mutex.Release();
        }

        ~MappedFile()
        {
            _mutex.Acquire(INFINITE);
            delete &_hFileMapping;
            delete &_hFile;
            _mutex.Release();
            delete &_mutex;
        }

        [[nodiscard]] LPVOID GetPointer() const
        {
            return MapViewOfFile(_hFileMapping.Handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        }
    };
}
