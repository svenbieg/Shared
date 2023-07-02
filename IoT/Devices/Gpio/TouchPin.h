//============
// TouchPin.h
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
// Touch-Pin
//===========

class TouchPin: public GpioPin
{
public:
	// Con-/Destructors
	TouchPin(Handle<String> Id, BYTE Pin);
	~TouchPin();

	// Common
	Event<TouchPin> Released;
	Event<TouchPin> Touched;
	Handle<Bool> Value;

private:
	// Common
	VOID DoSet(BOOL Value);
	WORD GetTreshold();
	VOID OnClockTick();
	WORD uAverage;
	WORD uAvgCount;
};

}}