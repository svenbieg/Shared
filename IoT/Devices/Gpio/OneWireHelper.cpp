//===================
// OneWireHelper.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "OneWireHelper.h"
#include "TaskLock.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//========
// Common
//========

BOOL OneWireReadBit(BYTE pin)
{
TaskLock lock;
SetPinMode(pin, PinMode::Output);
DigitalWrite(pin, 0);
SleepMicroseconds(6);
SetPinMode(pin, PinMode::Input);
DigitalWrite(pin, 1);
SleepMicroseconds(9);
BOOL value=DigitalRead(pin);
SleepMicroseconds(55);
return value;
}

BOOL OneWireReset(BYTE pin)
{
SetPinMode(pin, PinMode::Input);
UINT uretry=128;
while(!DigitalRead(pin))
	{
	if(--uretry==0)
		return false;
	}
TaskLock lock;
SetPinMode(pin, PinMode::Output);
SleepMicroseconds(0);
DigitalWrite(pin, 0);
SleepMicroseconds(480);
SetPinMode(pin, PinMode::Input);
DigitalWrite(pin, 1);
SleepMicroseconds(70);
bool value=DigitalRead(pin);
SleepMicroseconds(410);
return !value;
}

VOID OneWireWriteBit(BYTE pin, BOOL value)
{
UINT delay1=value? 6: 60;
UINT delay2=value? 64: 10;
TaskLock lock;
SetPinMode(pin, PinMode::Output);
DigitalWrite(pin, 0);
SleepMicroseconds(delay1);
DigitalWrite(pin, 1);
SleepMicroseconds(delay2);
}

}}