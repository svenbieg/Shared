//================
// WebContext.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "WebContext.h"

using namespace Culture;


//===========
// Namespace
//===========

namespace Web {


//==================
// Con-/Destructors
//==================

WebContext::WebContext(Web::WebSite* web_site):
Language(LanguageCode::None),
Protocol(nullptr),
TimeStamp(0),
WebSite(web_site)
{}

}