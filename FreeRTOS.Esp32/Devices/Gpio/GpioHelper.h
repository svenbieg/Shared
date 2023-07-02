//==============
// GpioHelper.h
//==============

#pragma once


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==========
// Pin-Mode
//==========

enum class PinMode
{
Output=0,
Input=1
};


//========
// Common
//========

BOOL DigitalRead(BYTE Pin);
VOID DigitalWrite(BYTE Pin, BOOL Set);
VOID SetPinMode(BYTE Pin, PinMode Mode);


//============
// Interrupts
//============

VOID AttachInterrupt(BYTE Pin);
VOID DetachInterrupt(BYTE Pin);
BOOL DetectInterrupt(BYTE Pin);

}}
