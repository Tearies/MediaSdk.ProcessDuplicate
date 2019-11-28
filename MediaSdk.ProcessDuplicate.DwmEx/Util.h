#pragma once

#include <windows.h>
#include "d3d11.h"
#include "tchar.h"
#include "wincodec.h"
using namespace System;

namespace MediaSdk
{
	namespace ProcessDuplicate
	{
		namespace Common
		{
			typedef BOOL(WINAPI* PFDwmGetDxSharedSurface)(
				HANDLE hHandle,
				HANDLE* phSurface,
				LUID* pAdapterLuid,
				ULONG* pFmtWindow,
				ULONG* pPresentFlags,
				ULONGLONG* pWin32kUpdateId
				);
			struct StringConvA
			{
				char* szAnsi;
				StringConvA(System::String^ s)
					:
					szAnsi(static_cast<char*>(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s).ToPointer()))

				{}
				~StringConvA()
				{
					System::Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr(szAnsi));
				}
				operator LPCSTR() const
				{
					return szAnsi;
				}
			};
			struct StringConvW
			{
				wchar_t* szUnicode;
				StringConvW(System::String^ s)
					:
					szUnicode(static_cast<wchar_t*>(System::Runtime::InteropServices::Marshal::StringToHGlobalUni(s).ToPointer()))

				{}
				~StringConvW()
				{
					System::Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr(szUnicode));
				}
				operator LPCWSTR() const
				{
					return szUnicode;
				}
			};

#define StringConvT StringConvW

#define StringConvT StringConvA

			public ref class Util
			{
			public:
				template <typename T>
				static T LoadWinAPILibraryAs(LPCSTR libName, LPCSTR funcName)
				{
					HMODULE hUser32Dll = LoadLibraryA(libName);
					return (T)GetProcAddress(hUser32Dll, funcName);
				}
				/**
				 * @brief 将纹理保存到本地
				 */
				static void SaveTextureToBmp(String^ fileName, ID3D11Texture2D* Texture);
			};
		}
	}
}
