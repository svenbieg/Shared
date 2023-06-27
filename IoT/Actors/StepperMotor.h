//================
// StepperMotor.h
//================

#pragma once


//=======
// Using
//=======

#include "Devices/Timer.h"


//===========
// Namespace
//===========

namespace Actors {


//===============
// Stepper-Motor
//===============

class StepperMotor: public Object
{
private:
	// Using
	using Timer=Devices::Timer;

public:
	// Con-/Destructors
	StepperMotor(BYTE Pin1, BYTE Pin2, BYTE Pin3, BYTE Pin4);
	~StepperMotor();

	// Common
	VOID Backward(UINT Steps=-1);
	VOID Forward(UINT Steps=-1);
	FLOAT Speed;
	VOID Stop();

private:
	// Common
	VOID OnTimerTriggered();
	Handle<Timer> hTimer;
	BYTE uPhase;
	BYTE uPin1;
	BYTE uPin2;
	BYTE uPin3;
	BYTE uPin4;
	UINT uSteps;
};

}