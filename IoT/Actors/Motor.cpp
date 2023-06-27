//===========
// Motor.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "Devices/Gpio/PwmHelper.h"
#include "Motor.h"

using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Actors {


//==================
// Con-/Destructors
//==================

Motor::Motor(Handle<String> id, BYTE pin_speed, BYTE pin_fwd, BYTE pin_back):
uPinBackward(pin_back),
uPinForward(pin_fwd),
uPinSpeed(pin_speed)
{
SetPinMode(uPinBackward, PinMode::Output);
SetPinMode(uPinForward, PinMode::Output);
PwmInit(uPinSpeed, 5000);
Speed=new Float(id, 0.f);
Speed->Changed.Add(this, &Motor::OnSpeedChanged);
}


//================
// Common Private
//================

VOID Motor::OnSpeedChanged()
{
FLOAT speed=Speed;
speed=MAX(speed, -1);
speed=MIN(speed, 1.);
DigitalWrite(uPinForward, speed>0.f);
DigitalWrite(uPinBackward, speed<0.f);
if(speed<0.f)
	speed*=-1.f;
UINT duty=(UINT)(speed*5000);
PwmSetDuty(uPinSpeed, duty);
}

}
