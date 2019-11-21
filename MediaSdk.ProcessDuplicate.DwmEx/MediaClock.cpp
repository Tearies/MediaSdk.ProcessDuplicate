#include "pch.h"
#include "MediaClock.h"

using namespace MediaSdk::Clock;

void MediaContext::OnTimerTick(Object^ sender)
{
	OnClockTick(nullptr);
}

void MediaContext::Start()
{
	mediaTimer->Change(timerInterval, timerInterval);
}

void MediaContext::Stop()
{
	mediaTimer->Change(Timeout::Infinite, timerInterval);
}

MediaContext::MediaContext():
	mediaTimer(nullptr),
	timerInterval(MediaTimerInterval)
{
	TimerCallback^ timerCallBack = gcnew TimerCallback(this, &MediaContext::OnTimerTick);
	mediaTimer = gcnew Timer(timerCallBack, nullptr, Timeout::Infinite, Timeout::Infinite);
}

MediaContext::~MediaContext()
{
	delete mediaTimer;
}

void MediaContext::OnClockTick(EventArgs^ args)
{
	ClockTick(nullptr, args);
}
