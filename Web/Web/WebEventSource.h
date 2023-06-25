//==================
// WebEventSource.h
//==================

#pragma once


//===========
// Namespace
//===========

namespace Web {


//======================
// Forward-Declarations
//======================

class WebContext;
class WebPage;

namespace Elements
{
class WebVariable;
}


//=========
// Scripts
//=========

extern LPCSTR WebEventSourceScript;


//=======
// Flags
//=======

enum class WebEventSourceFlags: UINT
{
None=0,
Event=1,
Closing=2,
Waiting=4
};


//==================
// Web-Event-Source
//==================

class WebEventSource: public Object
{
public:
	// Using
	using WebVariable=Web::Elements::WebVariable;

	// Con-/Destructors
	WebEventSource(WebPage* Page);
	~WebEventSource();

	// Common
	VOID RequestGet(Handle<WebContext> Context);

private:
	// Common
	VOID DoResponse();
	VOID OnPageChanged();
	Mutex cMutex;
	Signal cSignal;
	WebPage* pWebPage;
	WebEventSourceFlags uFlags;
};

}