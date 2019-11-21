#pragma once

#include <windows.h>
#include "d3d11.h"
#include "tchar.h"

using namespace System;

namespace MediaSdk
{
	namespace ProcessDuplicate
	{
		namespace Common
		{
			typedef BOOL (WINAPI* PFDwmGetDxSharedSurface)(
				HANDLE hHandle,
				HANDLE* phSurface,
				LUID* pAdapterLuid,
				ULONG* pFmtWindow,
				ULONG* pPresentFlags,
				ULONGLONG* pWin32kUpdateId
			);

			public ref class Util
			{
			public:
				template <typename T>
				static T LoadWinAPILibraryAs(LPCSTR libName, LPCSTR funcName)
				{
					HMODULE hUser32Dll = LoadLibraryA(libName);
					return (T)GetProcAddress(hUser32Dll, funcName);
				}
			};
		}
	}
}
