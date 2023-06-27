//=========
// Servo.h
//=========

#pragma once


//=======
// Using
//=======

#include "IntegerClasses.h"


//===========
// Namespace
//===========

namespace Actors {


//=======
// Servo
//=======

class Servo: public Object
{
public:
	// Con-/Destructors
	Servo(Handle<String> Id, BYTE Pin);

	// Common
	Handle<Int32> Position;

private:
	// Common
	VOID OnPositionChanged();
	BYTE uPin;
};

}
