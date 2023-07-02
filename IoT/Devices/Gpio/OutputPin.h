//=============
// OutputPin.h
//=============

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


//============
// Output-Pin
//============

class OutputPin: public GpioPin
{
public:
	// Con-/Destructors
	OutputPin(Handle<String> Id, BYTE Pin, BOOL Value=false);

	// Common
	Event<OutputPin> Down;
	Event<OutputPin> Up;
	Handle<Bool> Value;

private:
	// Common
	VOID OnValueChanged();
};

}}
