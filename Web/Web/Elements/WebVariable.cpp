//=================
// WebVariable.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "Web/WebEventSource.h"
#include "WebVariable.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//============================
// Con-/Destructors Protected
//============================

WebVariable::WebVariable(HtmlNode* parent, LPCSTR tag, Handle<String> id):
WebControl(parent, tag, id)
{
Document->AddScript(WebEventSourceScript);
}

}}