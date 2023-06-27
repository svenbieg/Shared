//============
// PwmPin.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/PwmHelper.h"
#include "PwmPin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

PwmPin::PwmPin(Handle<String> id, BYTE pin, UINT period):
GpioPin(id, pin),
uPeriod(period)
{
PwmInit(uPin, uPeriod);
Value=new Float(id, 0.f);
Value->Changed.Add(this, &PwmPin::OnValueChanged);
}


//================
// Common Private
//================

VOID PwmPin::OnValueChanged()
{
PwmSetDuty(uPin, (UINT)(Value*uPeriod));
}

}}
