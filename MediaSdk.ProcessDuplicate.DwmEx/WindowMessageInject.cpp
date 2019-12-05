#include "pch.h"
#include "WindowMessageInject.h"
#include <tchar.h>
#include <cstring>
#include <string>
#include "oleacc.h"

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

			void CALLBACK MessageProcess(HWINEVENTHOOK hWinEventHook,
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
					switch (event)
					{
					case EVENT_SYSTEM_MOVESIZESTART:
					case EVENT_SYSTEM_MOVESIZEEND:
					case EVENT_SYSTEM_MINIMIZESTART:
					case EVENT_SYSTEM_MINIMIZEEND:
						::SendMessageA((HWND)temp, VBIDEFINEMSGCODE, 0, 0);
						break;
					}

				}
			}

			void WindowMessageInject::Start()
			{
				DWORD processID;
				DWORD threadID;
				threadID = GetWindowThreadProcessId(this->TargetHandle, &processID);
				this->ProcessID = processID;
				this->ThreadID = threadID;
				Hook = SetWinEventHook(EVENT_MIN, EVENT_MAX, GetModuleHandleA("MediaSdk.ProcessDuplicate.DwmEx.dll"), MessageProcess, processID, threadID, WINEVENT_INCONTEXT | WINEVENT_SKIPOWNPROCESS);
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
