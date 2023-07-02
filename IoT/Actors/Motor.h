//=========
// Motor.h
//=========

#pragma once


//=======
// Using
//=======

#include "FloatClass.h"


//===========
// Namespace
//===========

namespace Actors {


//=======
// Motor
//=======

class Motor: public Object
{
public:
	// Con-/Destructors
	Motor(Handle<String> Id, BYTE PinSpeed, BYTE PinForward, BYTE PinBackward);

	// Common
	Handle<Float> Speed;

private:
	// Common
	VOID OnSpeedChanged();
	BYTE uPinBackward;
	BYTE uPinForward;
	BYTE uPinSpeed;
};

}
