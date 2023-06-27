//================
// ImpulsePin.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/ImpulseHelper.h"
#include "Devices/Clock.h"
#include "ImpulsePin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

ImpulsePin::ImpulsePin(Handle<String> id, BYTE pin):
GpioPin(id, pin)
{
ImpulsesPerSecond=new Int32(id);
ImpulseInit(uPin);
auto clock=Clock::Get();
clock->Second.Add(this, &ImpulsePin::OnClockSecond);
}

ImpulsePin::~ImpulsePin()
{
ImpulseClose(uPin);
auto clock=Clock::Get();
clock->Second.Remove(this);
}


//================
// Common Private
//================

VOID ImpulsePin::OnClockSecond()
{
ImpulsesPerSecond=ImpulseCount(uPin);
ImpulseClear(uPin);
}

}}