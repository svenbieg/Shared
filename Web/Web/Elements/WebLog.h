//==========
// WebLog.h
//==========

#pragma once


//=======
// Using
//=======

#include "Collections/Log.h"
#include "WebButton.h"
#include "WebVariable.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//=========
// Web-Log
//=========

class WebLog: public WebVariable
{
public:
	// Using
	using Log=Collections::Log;

	// Con-/Destructors
	WebLog(HtmlNode* Parent, Handle<String> Id, Handle<Log> Log);
	~WebLog();

	// Common
	SIZE_T UpdateToStream(OutputStream* Stream, WebContext* Context)override;
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Common
	VOID OnClearButtonClicked();
	VOID OnLogChanged();
	Handle<Log> hLog;
	UINT64 uTimeChanged;
};

}}