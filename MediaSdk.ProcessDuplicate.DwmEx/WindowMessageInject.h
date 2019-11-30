#pragma once
#include <windows.h>
#include <WinUser.h>
using namespace System;

namespace MediaSdk
{
	namespace ProcessDuplicate
	{
		namespace Common
		{
			LRESULT  MessageProcess(int Code, WPARAM wParam, LPARAM lParam);
			public ref class WindowMessageInject
			{
			private:
				HWND targetHandle = 0;
				DWORD ThreadID;
				DWORD ProcessID;
				HHOOK Hook;

			public:
			
				property HWND TargetHandle
				{
					HWND get()
					{
						return targetHandle;
					}
					void set(HWND handle)
					{
						targetHandle = handle;
					}
				}

				void Start();
			};

		}
	}
}