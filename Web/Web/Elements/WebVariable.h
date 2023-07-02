//===============
// WebVariable.h
//===============

#pragma once


//=======
// Using
//=======

#include "Variable.h"
#include "WebControl.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//==============
// Web-Variable
//==============

class WebVariable: public WebControl
{
public:
	// Common
	virtual SIZE_T UpdateToStream(OutputStream* Stream, WebContext* Context)=0;

protected:
	// Con-/Destructors
	WebVariable(HtmlNode* Parent, LPCSTR Tag, Handle<String> Id);
};

}}