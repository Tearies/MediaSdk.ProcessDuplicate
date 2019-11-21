#pragma once
#include "DwmEx.h"
#include "MediaClock.h"
#include "D3D11Image.h"
#include "ProcessConfiguration.h"

using namespace MediaSdk::DwmEx;
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
			 * @brief DWM��չ����
			 */
			DwmExManager^ dwm_ex_manager;

			/**
			 * ý��������
			 */
			MediaContext^ media_context;
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

		public:
			ProcessDuplicateManager();
			~ProcessDuplicateManager();

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
		};
	}
}
