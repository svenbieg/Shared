//================
// WebControl.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Web/WebPage.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//============================
// Con-/Destructors Protected
//============================

WebControl::WebControl(HtmlNode* parent, LPCSTR tag, Handle<String> id):
HtmlNode(parent, tag, id),
Page(dynamic_cast<WebPage*>(Document))
{
Page->Controls->Add(Id, this);
}

WebControl::~WebControl()
{
Page->Controls->Remove(Id);
}

}}