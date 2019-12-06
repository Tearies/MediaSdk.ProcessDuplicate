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
			 * ý��������
			 */
			MediaContext^ media_context;
			void SetPixelSize();
			void OnDelayStart();
			/**
			 * @brief ʱ�Ӽ�ʱ�ص�
			 */
			void OnClockTick(Object^ sender, EventArgs^ args);


			/**
			 * @brief ��������������
			 */
			ProcessConfiguration^ process_configuration;

			/**
			 * @brief Ŀ�����
			 */
			Process^ targetProcess;
			/*
			 * @brief ������Ϣ����
			 */
			MessageWindow^ messageWindow;
			int m_surfWidth;
			int m_surfHeight;
		public:
			ProcessDuplicateManager(int surfWidth,int surfHeight);
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
			 * @brief ��ʼ���̾����� \n
			 *	@param  configuration ���̾����ƵĲ���
			 */
			void Start(ProcessConfiguration^ configuration);
			/**
			 * @brief ����������,�˲�����رս���
			 */
			void End();
			void OnTargetSizeChanged(System::Object^ sender, System::EventArgs^ e);
			void OnShutdownStarted(System::Object^ sender, System::EventArgs^ e);
			void OnExited(System::Object^ sender, System::EventArgs^ e);
		};
	}
}
