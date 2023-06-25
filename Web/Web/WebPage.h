//===========
// WebPage.h
//===========

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Html/HtmlDocument.h"
#include "Web/Elements/WebVariable.h"


//===========
// Namespace
//===========

namespace Web {


//==========
// Web-Page
//==========

class WebPage: public Html::HtmlDocument
{
public:
	// Using
	using WebContext=WebContext;
	using WebControl=Elements::WebControl;
	using WebControlMap=Collections::Map<Handle<String>, WebControl*>;
	using WebVariable=Elements::WebVariable;

	// Con-/Destructors
	WebPage();

	// Common
	Event<WebPage> Changed;
	Handle<WebControlMap> Controls;
	virtual VOID RequestGet(Handle<WebContext> Context);
	virtual VOID RequestNotify(Handle<WebContext> Context);
	virtual VOID RequestPost(Handle<WebContext> Context);
};

}