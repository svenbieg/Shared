//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "Collections/Log.h"
#include "Collections/Settings.h"
#include "Console/Application.h"
#include "Network/Ota/OtaUpdate.h"
#include "Runtime/Shell.h"
#include "StringVariable.h"


//===========
// Namespace
//===========

namespace IoT {


//=============
// Application
//=============

class Application: public Console::Application
{
public:
	// Using
	using OtaUpdate=Network::Ota::OtaUpdate;

	// Common
	static Handle<Application> Current;
	Handle<Collections::Log> Log;
	Handle<Collections::Settings> Settings;
	Handle<Runtime::Shell> Shell;
	VOID Update();
	Handle<StringVariable> UpdateStatus;

protected:
	// Con-/Destructors
	Application(LPCSTR Name, Handle<String> UpdateUrl=nullptr);

private:
	// Common
	VOID OnOtaUpdateFailed();
	VOID OnOtaUpdateStatus(Handle<String> Status);
	VOID OnOtaUpdateSuccessful();
	Handle<OtaUpdate> hUpdate;
	Handle<String> hUpdateUrl;
};

}