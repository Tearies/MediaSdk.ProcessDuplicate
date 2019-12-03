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

			public  class WindowMessageInject
			{
			private:
				HWND targetHandle = 0;
				DWORD ThreadID;
				DWORD ProcessID;
				HHOOK Hook;
				WPARAM BuildWParam(int Code, WPARAM w_param, LPARAM l_param);
				LRESULT  MessageProcess(int Code, WPARAM wParam, LPARAM lParam);
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