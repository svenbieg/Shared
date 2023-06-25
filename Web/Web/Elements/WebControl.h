//==============
// WebControl.h
//==============

#pragma once


//=======
// Using
//=======

#include "Html/Elements/HtmlNode.h"
#include "Web/WebContext.h"


//======================
// Forward-Declarations
//======================

namespace Web
{
class WebPage;
}


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//=============
// Web-Control
//=============

class WebControl: public Html::Elements::HtmlNode
{
public:
	// Common
	virtual VOID OnNotified(Handle<WebContext> Context) {}
	WebPage* const Page;

protected:
	// Con-/Destructors
	WebControl(HtmlNode* Parent, LPCSTR Tag, Handle<String> Id);
	virtual ~WebControl();
};

}}