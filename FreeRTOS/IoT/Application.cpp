//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Application.h"


//===========
// Namespace
//===========

namespace IoT {


//========
// Common
//========

Handle<Application> Application::Current;

VOID Application::Update()
{
if(!hUpdateUrl)
	return;
hUpdate=new OtaUpdate();
hUpdate->Failed.Add(this, &Application::OnOtaUpdateFailed);
hUpdate->Status.Add(this, &Application::OnOtaUpdateStatus);
hUpdate->Successful.Add(this, &Application::OnOtaUpdateSuccessful);
hUpdate->Begin(hUpdateUrl);
}


//============================
// Con-/Destructors Protected
//============================

Application::Application(LPCSTR name, Handle<String> url):
Console::Application(name),
hUpdateUrl(url)
{
Current=this;
Log=new Collections::Log();
Settings=new Collections::Settings();
Shell=new Runtime::Shell(Console);
UpdateStatus=new StringVariable("UpdateStatus");
}


//================
// Common Private
//================

VOID Application::OnOtaUpdateFailed()
{
hUpdate=nullptr;
}

VOID Application::OnOtaUpdateStatus(Handle<String> status)
{
UpdateStatus=status;
}

VOID Application::OnOtaUpdateSuccessful()
{
Log->Write("Update installiert");
hUpdate=nullptr;
}

}