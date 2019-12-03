#include "pch.h"
#include "WindowMessageInject.h"
#include <tchar.h>
#include <cstring>
#include <string>


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

			void CALLBACK  WindowMessageInject::MessageProcess(HWINEVENTHOOK hWinEventHook,
				DWORD event,
				HWND hwnd,
				LONG idObject,
				LONG idChild,
				DWORD idEventThread,
				DWORD dwmsEventTime)
			{

				auto remotingHandle = Environment::GetEnvironmentVariable(RemottingSharedHandle);
				int temp;
				if (int::TryParse(remotingHandle, temp))
				{
					 
					::SendMessageA((HWND)temp, VBIDEFINEMSGCODE, 0, 0);

				}
			}

			void WindowMessageInject::Start()
			{

				DWORD processID;
				DWORD threadID;
				threadID = GetWindowThreadProcessId(this->TargetHandle, &processID);
				this->ProcessID = processID;
				this->ThreadID = threadID;

				Hook = SetWinEventHook(EVENT_SYSTEM_MINIMIZESTART, EVENT_SYSTEM_MINIMIZEEND, GetModuleHandleA("MediaSdk.ProcessDuplicate.DwmEx.dll"), pointer_cast<WINEVENTPROC>(&WindowMessageInject::MessageProcess), processID, threadID, WINEVENT_INCONTEXT | WINEVENT_SKIPOWNPROCESS);
				DWORD error = GetLastError();
				HRESULT hr = HRESULT_FROM_WIN32(error);
			}

			void WindowMessageInject::Stop()
			{
				UnhookWinEvent(Hook);
			}
		}
	}
}
