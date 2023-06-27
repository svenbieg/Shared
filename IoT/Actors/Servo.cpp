//===========
// Servo.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/PwmHelper.h"
#include "Servo.h"

using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Actors {


//==================
// Con-/Destructors
//==================

Servo::Servo(Handle<String> hid, BYTE upin):
uPin(upin)
{
PwmInit(uPin, 10000);
Position=new Int32(hid, 0);
Position->Changed.Add(this, &Servo::OnPositionChanged);
}


//================
// Common Private
//================

VOID Servo::OnPositionChanged()
{
INT ipos=Position;
FLOAT fpos=(FLOAT)ipos/90.f;
UINT uduty=(UINT)(1500+fpos*500);
PwmSetDuty(uPin, uduty);
}

}
