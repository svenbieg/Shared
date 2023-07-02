//==========
// System.h
//==========

#pragma once


//=======
// Using
//=======

#include "Physics/TimePoint.h"


//===========
// Namespace
//===========

namespace System {


//===============
// Wakeup-Reason
//===============

enum class WakeupReason
{
None,
Timer,
Touchpad
};


//========
// System
//========

class System: public Object
{
public:
	// Common
	static WakeupReason GetWakeupReason();
	static VOID Reset();
	static VOID Restart();
	static VOID Sleep(UINT Millis);
	static VOID SleepTouchable(UINT Millis);
	static Handle<Physics::TimePoint> Start;
	static const FLOAT Voltage;
};

}