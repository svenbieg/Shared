//============
// WebLogin.h
//============

#pragma once


//=======
// Using
//=======

#include "Html/Elements/HtmlNode.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//===========
// Web-Login
//===========

class WebLogin: public Html::Elements::HtmlNode
{
public:
	// Con-/Destructors
	WebLogin(HtmlNode* Parent);

	Handle<String> LoginUrl;
	Handle<String> LogoutUrl;

protected:
	// Common
	SIZE_T WriteElementsToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;
};

}}