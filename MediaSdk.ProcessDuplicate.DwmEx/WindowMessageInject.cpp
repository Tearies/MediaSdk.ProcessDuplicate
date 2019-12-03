#include "pch.h"
#include "WindowMessageInject.h"
#include <tchar.h>
 

namespace MediaSdk
{
	namespace ProcessDuplicate
	{
		namespace Common
		{
			UINT BROADCAST_Message;
			WindowMessageInject::WindowMessageInject() : ThreadID(0), ProcessID(0), Hook(nullptr)
			{
			}

			 

			WPARAM WindowMessageInject::BuildWParam(int Code, WPARAM w_param, LPARAM l_param)
			{
				BROADCAST_MESSAGE broadcast_message;
				broadcast_message.ProcessID = GetCurrentProcessId();
				broadcast_message.ReleativeWParam = w_param;
				broadcast_message.MSG = Code;
				broadcast_message.ReleativeLParam = l_param;
				return reinterpret_cast<WPARAM>(&broadcast_message);
			}

			LRESULT  WindowMessageInject::MessageProcess(const int Code, WPARAM wParam, LPARAM lParam)
			{
				auto remotingHandle= Environment::GetEnvironmentVariable(RemottingSharedHandle);
				int temp;
				if(int::TryParse(remotingHandle,temp))
				{
					::SendMessageA((HWND)temp, Code, wParam, lParam);
				}
				return CallNextHookEx(NULL,Code,wParam,lParam);
			}

			void WindowMessageInject::Start()
			{
				BROADCAST_Message = ::RegisterWindowMessageA("MediaSdk.ProcessDuplicate_BROADCAST_MESSAGE");
				DWORD processID;
				DWORD threadID;
				threadID = GetWindowThreadProcessId(this->TargetHandle, &processID);
				this->ProcessID = processID;
				this->ThreadID = threadID;
				Hook = SetWindowsHookExA(WH_MSGFILTER, pointer_cast<HOOKPROC>(&WindowMessageInject::MessageProcess), GetModuleHandleA("MediaSdk.ProcessDuplicate.DwmEx.dll"), threadID);
				DWORD error = GetLastError();
				HRESULT hr = HRESULT_FROM_WIN32(error);
			}

			void WindowMessageInject::Stop()
			{
				UnhookWindowsHookEx(Hook);
			}
		}
	}
}
