//=========
// Timer.h
//=========

#pragma once


//===========
// Namespace
//===========

namespace System {


//=======
// Timer
//=======

class Timer: public Object
{
public:
	// Con-/Destructors
	Timer();
	~Timer();

	// Common
	BOOL IsStarted()const { return pTimer!=nullptr; }
	VOID StartOnce(UINT MilliSeconds);
	VOID StartPeriodic(UINT MilliSeconds);
	VOID Stop();
	Event<Timer> Triggered;

private:
	// Common
	VOID OnTriggered();
	Handle<Timer> hCallback;
	VOID* pTimer;
};

}