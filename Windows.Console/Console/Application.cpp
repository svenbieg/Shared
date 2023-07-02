//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Application.h"
#include "CommandLine.h"

extern VOID Initialize();


//=========
// Globals
//=========

DWORD MainThreadId=0;


//==========
// Callback
//==========

BOOL WINAPI ConsoleCallback(DWORD id)
{
if(id==CTRL_CLOSE_EVENT)
	{
	PostThreadMessage(MainThreadId, WM_QUIT, 0, 0);
	return true;
	}
return false;
}


//=============
// Entry-Point
//=============

INT main()
{
SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
MainThreadId=GetCurrentThreadId();
SetConsoleCtrlHandler(ConsoleCallback, true);
new CommandLine(GetCommandLineA());
Initialize();
INT status=0;
auto app=Console::Application::Current;
if(app)
	{
	status=app->Run();
	app->Quit();
	}
return status;
}


//===========
// Namespace
//===========

namespace Console {


//========
// Common
//========

Application* Application::Current=nullptr;

INT Application::Run()
{
INT status=0;
MSG msg;
while(GetMessage(&msg, NULL, 0, 0))
	{
	if(msg.message==WM_QUIT)
		{
		status=(INT)msg.wParam;
		break;
		}
	HandleDispatched();
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
return status;
}


//============================
// Con-/Destructors Protected
//============================

Application::Application(LPCSTR name):
Core::Application(name)
{
Current=this;
Dispatched.Add(this, &Application::OnDispatched);
Console=::Console::Console::Open();
}


//================
// Common Private
//================

VOID Application::OnDispatched()
{
PostMessage(NULL, WM_DISPATCH, 0, 0);
}

}