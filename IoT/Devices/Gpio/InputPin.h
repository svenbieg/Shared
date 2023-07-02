//============
// InputPin.h
//============

#pragma once


//=======
// Using
//=======

#include "BoolClass.h"
#include "GpioPin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//===========
// Input-Pin
//===========

class InputPin: public GpioPin
{
public:
	// Con-/Destructors
	InputPin(Handle<String> Id, BYTE Pin);
	~InputPin();

	// Common
	Event<InputPin> Down;
	Event<InputPin> Up;
	Handle<Bool> Value;

private:
	// Common
	VOID DoChange();
	VOID OnClockTick();
};

}}
