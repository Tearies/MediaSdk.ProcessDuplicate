#pragma once
using namespace System;
using namespace System::Threading;

namespace MediaSdk
{
	namespace Clock
	{
		/**
		 * \brief ��ý��ʱ�Ӽ��
		 */
		const UInt16 MediaTimerInterval = 0x21U;

		public ref class MediaContext : IDisposable
		{
		private:
			UInt16 timerInterval;
			Timer^ mediaTimer;
			void OnTimerTick(Object^ sender);
		public:
			event EventHandler^ ClockTick; //��ý��ʱ��
			void Start(); //��ʼʱ�Ӽ�ʱ
			void Stop(); //ֹͣ��ʱ
			MediaContext();
			virtual ~MediaContext();
		protected:
			virtual void OnClockTick(EventArgs^ args);
		};
	}
}
