//==============
// WebSession.h
//==============

#pragma once


//=======
// Using
//=======

#include "Network/Http/HttpRequest.h"
#include "WebAccount.h"
#include "WebEventSource.h"


//===========
// Namespace
//===========

namespace Web {


//=============
// Web-Session
//=============

class WebSession: public Object
{
public:
	// Using
	using HttpRequest=Network::Http::HttpRequest;

	// Con-/Destructors
	WebSession(Handle<String> Id);

	// Common
	Handle<WebAccount> Account;
	Mutex CriticalSection;
	Handle<WebEventSource> EventSource;
	Handle<String> const Id;
	UINT64 TimeOut;
};

}