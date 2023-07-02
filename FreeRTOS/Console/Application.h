//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "Framework/Application.h"
#include "Devices/Serial/SerialPort.h"


//===========
// Namespace
//===========

namespace Console {


//=============
// Application
//=============

class Application: public Framework::Application
{
public:
	// Using
	using SerialPort=Devices::Serial::SerialPort;

	// Con-/Destructors
	Application(LPCSTR Name);

	// Common
	Handle<SerialPort> Console;
	static Application* Current;
	VOID Run();

private:
	// Common
	VOID OnDispatched();
	Signal cDispatched;
	Mutex cMutex;
	DispatchedHandler* pFirst;
	DispatchedHandler* pLast;
};

}