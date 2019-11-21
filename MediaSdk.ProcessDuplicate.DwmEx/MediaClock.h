#pragma once
using namespace System;
using namespace System::Threading;

namespace MediaSdk
{
	namespace Clock
	{
		/**
		 * \brief 多媒体时钟间隔
		 */
		const UInt16 MediaTimerInterval = 0x21U;

		public ref class MediaContext : IDisposable
		{
		private:
			UInt16 timerInterval;
			Timer^ mediaTimer;
			void OnTimerTick(Object^ sender);
		public:
			event EventHandler^ ClockTick; //多媒体时钟
			void Start(); //开始时钟计时
			void Stop(); //停止计时
			MediaContext();
			virtual ~MediaContext();
		protected:
			virtual void OnClockTick(EventArgs^ args);
		};
	}
}
