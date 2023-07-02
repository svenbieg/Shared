//=============
// AnalogPin.h
//=============

#pragma once


//=======
// Using
//=======

#include "Math/Average.h"
#include "FloatClass.h"
#include "GpioPin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//============
// Analog Pin
//============

class AnalogPin: public GpioPin
{
public:
	// Con-/Destructors
	AnalogPin(Handle<String> Id, BYTE Pin);
	~AnalogPin();

	// Common
	FLOAT Read();
	Handle<Float> Value;

private:
	// Common
	VOID OnClockTick();
	Math::Average<FLOAT, 20, 4> fInput;
	Math::Average<FLOAT, 10> fValue;
};

}}
