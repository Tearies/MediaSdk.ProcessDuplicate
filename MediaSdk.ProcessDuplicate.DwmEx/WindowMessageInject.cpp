#include "pch.h"
#include "WindowMessageInject.h"
namespace MediaSdk
{
	namespace ProcessDuplicate
	{
		namespace Common
		{
			 
			LRESULT  MessageProcess(int Code, WPARAM wParam, LPARAM lParam)
			{
			 
				return 0;
			}

			void WindowMessageInject::Start()
			{
				DWORD processID;
				DWORD threadID;
				threadID = GetWindowThreadProcessId(this->TargetHandle, &processID);
				this->ProcessID = processID;
				this->ThreadID = threadID;
				HOOKPROC call_back=HOOKPROC(MessageProcess);
				Hook = SetWindowsHookExA(WH_MOUSE_LL, call_back, 0, 0);
				DWORD error=GetLastError();
				HRESULT hr = HRESULT_FROM_WIN32(error);
			}


		}
	}
}