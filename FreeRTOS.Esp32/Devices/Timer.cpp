//===========
// Timer.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include <esp_attr.h>
#include <esp_timer.h>
#include "Timer.h"


//===========
// Namespace
//===========

namespace Devices {


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

VOID Timer::StartOnce(UINT us)
{
ASSERT(pTimer==nullptr);
esp_timer_create_args_t args;
ZeroMemory(&args, sizeof(esp_timer_create_args_t));
args.arg=this;
args.callback=TimerProc;
esp_timer_handle_t ptimer=nullptr;
if(esp_timer_create(&args, &ptimer)!=ESP_OK)
	{
	DebugPrint("esp_timer_create() failed\n");
	return;
	}
hCallback=this;
pTimer=ptimer;
esp_timer_start_once(ptimer, us);
}

VOID Timer::StartPeriodic(UINT us)
{
ASSERT(pTimer==nullptr);
esp_timer_create_args_t args;
ZeroMemory(&args, sizeof(esp_timer_create_args_t));
args.arg=this;
args.callback=TimerProc;
esp_timer_handle_t ptimer=nullptr;
if(esp_timer_create(&args, &ptimer)!=ESP_OK)
	{
	DebugPrint("esp_timer_create() failed\n");
	return;
	}
hCallback=this;
pTimer=ptimer;
esp_timer_start_periodic(ptimer, us);
}

VOID Timer::Stop()
{
if(!pTimer)
	return;
esp_timer_handle_t ptimer=(esp_timer_handle_t)pTimer;
esp_timer_stop(ptimer);
esp_timer_delete(ptimer);
hCallback=nullptr;
pTimer=nullptr;
}


//================
// Common Private
//================

VOID Timer::TimerProc(VOID* pparam)
{
Handle<Timer> timer=(Timer*)pparam;
timer->Triggered(timer);
}

}