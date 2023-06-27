//==================
// StepperMotor.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Gpio/GpioHelper.h"
#include "StepperMotor.h"

using namespace Devices;
using namespace Devices::Gpio;


//===========
// Namespace
//===========

namespace Actors {


//==================
// Con-/Destructors
//==================

StepperMotor::StepperMotor(BYTE upin1, BYTE upin2, BYTE upin3, BYTE upin4):
Speed(1.f),
uPhase(0),
uPin1(upin1),
uPin2(upin2),
uPin3(upin3),
uPin4(upin4)
{
SetPinMode(uPin1, PinMode::Output);
SetPinMode(uPin2, PinMode::Output);
SetPinMode(uPin3, PinMode::Output);
SetPinMode(uPin4, PinMode::Output);
Stop();
}

StepperMotor::~StepperMotor()
{
Stop();
}


//========
// Common
//========

VOID StepperMotor::Backward(UINT usteps)
{
Stop();
if(Speed==0.f)
	return;
UINT udt=(UINT)(10000.f-Speed*9000.f);
uPhase=16;
uSteps=usteps;
hTimer=new Timer();
hTimer->Triggered.Add(this, &StepperMotor::OnTimerTriggered);
hTimer->StartPeriodic(udt);
}

VOID StepperMotor::Forward(UINT usteps)
{
Stop();
if(Speed==0.f)
	return;
UINT udt=(UINT)(10000.f-Speed*9000.f);
uPhase=0;
uSteps=usteps;
hTimer=new Timer();
hTimer->Triggered.Add(this, &StepperMotor::OnTimerTriggered);
hTimer->StartPeriodic(udt);
}

VOID StepperMotor::Stop()
{
if(hTimer)
	{
	hTimer->Stop();
	hTimer=nullptr;
	}
DigitalWrite(uPin1, false);
DigitalWrite(uPin2, false);
DigitalWrite(uPin3, false);
DigitalWrite(uPin4, false);
}


//================
// Common Private
//================

VOID StepperMotor::OnTimerTriggered()
{
switch(uPhase)
	{
	case 0:
	case 16:
		{
		DigitalWrite(uPin1, true);
		DigitalWrite(uPin2, false);
		DigitalWrite(uPin3, false);
		DigitalWrite(uPin4, false);
		break;
		}
	case 1:
	case 23:
		{
		DigitalWrite(uPin1, true);
		DigitalWrite(uPin2, true);
		DigitalWrite(uPin3, false);
		DigitalWrite(uPin4, false);
		break;
		}
	case 2:
	case 22:
		{
		DigitalWrite(uPin1, false);
		DigitalWrite(uPin2, true);
		DigitalWrite(uPin3, false);
		DigitalWrite(uPin4, false);
		break;
		}
	case 3:
	case 21:
		{
		DigitalWrite(uPin1, false);
		DigitalWrite(uPin2, true);
		DigitalWrite(uPin3, true);
		DigitalWrite(uPin4, false);
		break;
		}
	case 4:
	case 20:
		{
		DigitalWrite(uPin1, false);
		DigitalWrite(uPin2, false);
		DigitalWrite(uPin3, true);
		DigitalWrite(uPin4, false);
		break;
		}
	case 5:
	case 19:
		{
		DigitalWrite(uPin1, false);
		DigitalWrite(uPin2, false);
		DigitalWrite(uPin3, true);
		DigitalWrite(uPin4, true);
		break;
		}
	case 6:
	case 18:
		{
		DigitalWrite(uPin1, false);
		DigitalWrite(uPin2, false);
		DigitalWrite(uPin3, false);
		DigitalWrite(uPin4, true);
		break;
		}
	case 7:
	case 17:
		{
		DigitalWrite(uPin1, true);
		DigitalWrite(uPin2, false);
		DigitalWrite(uPin3, false);
		DigitalWrite(uPin4, true);
		break;
		}
	}
uPhase++;
if(uPhase==8)
	{
	uPhase=0;
	uSteps--;
	}
if(uPhase==24)
	{
	uPhase=16;
	uSteps--;
	}
if(uSteps==0)
	Stop();
}

}