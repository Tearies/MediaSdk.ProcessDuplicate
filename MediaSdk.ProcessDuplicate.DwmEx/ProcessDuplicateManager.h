#pragma once
#include "DwmEx.h"
#include "MediaClock.h"
#include "D3D11Image.h"
#include "ProcessConfiguration.h"

 
using namespace MediaSdk::Clock;
using namespace System::Diagnostics;
using namespace MediaSdk::Common;
using namespace MediaSdk::Controls;
using namespace Windows::Threading;

namespace MediaSdk
{
	namespace Common
	{
		public ref class ProcessDuplicateManager
		{
		private:
			Dispatcher^ currentUIDistpatcher;
			 

			/**
			 * 媒体上下文
			 */
			MediaContext^ media_context;
			/**
			 * @brief 时钟计时回调
			 */
			void OnClockTick(Object^ sender, EventArgs^ args);


			/**
			 * @brief 进程启动项配置
			 */
			ProcessConfiguration^ process_configuration;

			/**
			 * @brief 目标进程
			 */
			Process^ targetProcess;
			/*
			 * @brief 本地消息窗口
			 */
			MessageWindow^ messageWindow;
		public:
			ProcessDuplicateManager();
			~ProcessDuplicateManager();
			property IntPtr RemottingHandle
			{
				IntPtr get()
				{
					return messageWindow->Handle;
				}
			}
			void DoRender();
			/**
			 * @brief 开始进程镜像复制 \n
			 *	@param  configuration 进程镜像复制的参数
			 */
			void Start(ProcessConfiguration^ configuration);
			/**
			 * @brief 结束镜像复制,此操作会关闭进程
			 */
			void End();
			void OnTargetSizeChanged(System::Object^ sender, System::EventArgs^ e);
			void OnShutdownStarted(System::Object^ sender, System::EventArgs^ e);
			void OnExited(System::Object^ sender, System::EventArgs^ e);
		};
	}
}
