//===========
// Timer.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include "Timer.h"


//===========
// Namespace
//===========

namespace System {


//==========
// Callback
//==========

VOID TimerCallback(TimerHandle_t xtimer)
{
Handle<Timer> timer=(Timer*)pvTimerGetTimerID(xtimer);
timer->Triggered(timer);
}


//==================
// Con-/Destructors
//==================

Timer::Timer():
pTimer(nullptr)
{}

Timer::~Timer()
{
Stop();
}


//========
// Common
//========

VOID Timer::StartOnce(UINT ms)
{
ASSERT(pTimer==nullptr);
UINT ticks=MAX(ms/portTICK_PERIOD_MS, 1);
auto xtimer=xTimerCreate(nullptr, ticks, pdFALSE, this, TimerCallback);
if(xtimer==nullptr)
	{
	DebugPrint("xTimerCreate() failed\n");
	return;
	}
Triggered.Add(this, &Timer::OnTriggered);
hCallback=this;
pTimer=xtimer;
xTimerStart(xtimer, 0);
}

VOID Timer::StartPeriodic(UINT ms)
{
ASSERT(pTimer==nullptr);
UINT ticks=MAX(ms/portTICK_PERIOD_MS, 1);
auto xtimer=xTimerCreate(nullptr, ticks, pdTRUE, this, TimerCallback);
if(xtimer==nullptr)
	{
	DebugPrint("xTimerCreate() failed\n");
	return;
	}
hCallback=this;
pTimer=xtimer;
xTimerStart(xtimer, 0);
}

VOID Timer::Stop()
{
if(!pTimer)
	return;
auto timer=(TimerHandle_t)pTimer;
xTimerDelete(timer, 0);
hCallback=nullptr;
pTimer=nullptr;
}


//================
// Common Private
//================

VOID Timer::OnTriggered()
{
Stop();
}

}