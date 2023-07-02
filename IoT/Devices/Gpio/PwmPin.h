//==========
// PwmPin.h
//==========

#pragma once


//=======
// Using
//=======

#include "FloatClass.h"
#include "GpioPin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//=========
// PWM-Pin
//=========

class PwmPin: public GpioPin
{
public:
	// Con-/Destructors
	PwmPin(Handle<String> Id, BYTE Pin, UINT Period);

	// Common
	BYTE GetPin()const { return uPin; }
	Handle<Float> Value;

private:
	// Common
	VOID OnValueChanged();
	UINT uPeriod;
};

}}
