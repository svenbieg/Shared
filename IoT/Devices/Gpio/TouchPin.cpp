//==============
// TouchPin.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Core/Application.h"
#include "Devices/Gpio/TouchHelper.h"
#include "Devices/Clock.h"
#include "TouchPin.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

TouchPin::TouchPin(Handle<String> id, BYTE pin):
GpioPin(id, pin),
uAverage(0),
uAvgCount(0)
{
Value=new Bool(id);
if(!TouchInit(uPin))
	return;
auto clock=Clock::Get();
clock->Tick.Add(this, &TouchPin::OnClockTick);
}

TouchPin::~TouchPin()
{
TouchClose(uPin);
auto clock=Clock::Get();
clock->Tick.Remove(this);
}


//================
// Common Private
//================

VOID TouchPin::DoSet(BOOL value)
{
Value->Set(value);
value? Touched(this): Released(this);
}

WORD TouchPin::GetTreshold()
{
if(uAvgCount>=32)
	return uAverage;
WORD value=TouchRead(uPin);
uAverage+=value;
uAvgCount++;
if(uAvgCount<32)
	return 0;
uAverage=uAverage/32-100;
if(uAverage<200)
	{
	DebugPrint("Touch-Pin %u average too low\n", uPin);
	TouchClose(uPin);
	auto clock=Clock::Get();
	clock->Tick.Remove(this);
	return 0;
	}
TouchTreshold(uPin, uAverage);
return uAverage;
}

VOID TouchPin::OnClockTick()
{
WORD threshold=GetTreshold();
if(!threshold)
	return;
WORD value=TouchRead(uPin);
BOOL b_new=value<threshold;
BOOL b_old=Value;
if(b_old==b_new)
	return;
Application::Current->Dispatch(this, &TouchPin::DoSet, b_new);
}

}}