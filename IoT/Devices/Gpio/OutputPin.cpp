//===============
// OutputPin.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "OutputPin.h"

using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

OutputPin::OutputPin(Handle<String> id, BYTE pin, BOOL value):
GpioPin(id, pin)
{
SetPinMode(uPin, PinMode::Output);
DigitalWrite(uPin, value);
Value=new Bool(id, value);
Value->Changed.Add(this, &OutputPin::OnValueChanged);
}


//================
// Common Private
//================

VOID OutputPin::OnValueChanged()
{
BOOL value=Value;
DigitalWrite(uPin, value);
value? Up(this): Down(this);
}

}}
