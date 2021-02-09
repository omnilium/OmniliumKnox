#pragma once

#include "Core.h"
#include "RAIITemplates.h"

namespace OmniliumKnox {
	namespace Core {
		class CORE_API MappedFile {
			
		private:
			AutoHandle<HANDLE> _hFile = new AutoHandle<HANDLE>(INVALID_HANDLE_VALUE);
			AutoHandle<HANDLE> _hFileMapping = new AutoHandle<HANDLE>(INVALID_HANDLE_VALUE);
			AutoHandle<LPVOID> _hFileMapView = new AutoHandle<LPVOID>(NULL);
			AutoMutex _mutex;

		public:
			MappedFile(LPCWSTR lpFilePath) : _mutex(lpFilePath) {
				_mutex.Acquire(INFINITE);
				_hFile = CreateFile(lpFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				_hFileMapping = CreateFileMapping(_hFile.Handle, NULL, PAGE_READWRITE, 0, 1 << 20, lpFilePath);
				_mutex.Release();
			}

			~MappedFile() {
				_mutex.Acquire(INFINITE);
				delete& _hFileMapping;
				delete& _hFile;
				_mutex.Release();
				delete& _mutex;
			}

			LPVOID GetPointer() {
				return MapViewOfFile(_hFileMapping.Handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			}
		};
	}
}