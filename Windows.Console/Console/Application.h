//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "Core/Application.h"
#include "Console.h"


//===========
// Namespace
//===========

namespace Console {


//=============
// Application
//=============

class Application: public Core::Application
{
public:
	// Common
	Handle<Console> Console;
	static Application* Current;
	INT Run();

protected:
	// Con-/Destructors
	Application(LPCSTR Name);

private:
	// Common
	VOID OnDispatched();
};

}