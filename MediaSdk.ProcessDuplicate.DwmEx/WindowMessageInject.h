#pragma once
#include <windows.h>
using namespace System;
template<typename dst_type, typename src_type>
dst_type pointer_cast(src_type src)
{
	return *static_cast<dst_type*>(static_cast<void*>(&src));
}





namespace MediaSdk
{
	namespace ProcessDuplicate
	{
		namespace Common
		{
			void CALLBACK  MessageProcess(HWINEVENTHOOK hWinEventHook,
				DWORD event,
				HWND hwnd,
				LONG idObject,
				LONG idChild,
				DWORD idEventThread,
				DWORD dwmsEventTime);
			public  class WindowMessageInject
			{
			private:
				HWND targetHandle = 0;
				DWORD ThreadID;
				DWORD ProcessID;
				HWINEVENTHOOK Hook;
				
			public:
				WindowMessageInject();

				_declspec(property(get = GetTargetHandle, put = SetTargetHandle)) HWND TargetHandle;
				HWND GetTargetHandle()
				{
					return this->targetHandle;
				};
				void SetTargetHandle(HWND handle)
				{
					this->targetHandle = handle;
				}
				void Start();
				void Stop();
			};

		}
	}
}