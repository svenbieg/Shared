//==============
// ImpulsePin.h
//==============

#pragma once


//=======
// Using
//=======

#include "GpioPin.h"
#include "IntegerClasses.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//=============
// Impulse-Pin
//=============

class ImpulsePin: public GpioPin
{
public:
	// Con-/Destructors
	ImpulsePin(Handle<String> Id, BYTE Pin);
	~ImpulsePin();

	// Common
	Handle<Int32> ImpulsesPerSecond;

private:
	// Common
	VOID OnClockSecond();
	BYTE uPin;
};

}}