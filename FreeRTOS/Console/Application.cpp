//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Serial/SerialPort.h"
#include "Application.h"

using namespace Devices::Serial;


//===========
// Namespace
//===========

namespace Console {


//==================
// Con-/Destructors
//==================

Application::Application(LPCSTR name):
Framework::Application(name),
pFirst(nullptr),
pLast(nullptr)
{
Current=this;
Console=SerialPort::Open();
}


//========
// Common
//========

Application* Application::Current=nullptr;

VOID Application::Run()
{
ScopedLock lock(cMutex);
while(1)
	{
	cDispatched.Wait(lock);
	HandleDispatched();
	}
}


//================
// Common Private
//================

VOID Application::OnDispatched()
{
ScopedLock lock(cMutex);
cDispatched.Broadcast();
}

}