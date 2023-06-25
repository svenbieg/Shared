//=================
// HtmlCaption.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "HtmlCaption.h"
#include "HtmlText.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//==================
// Con-/Destructors
//==================

HtmlCaption::HtmlCaption(HtmlNode* parent, Handle<Sentence> text):
HtmlNode(parent, "h1")
{
new HtmlText(this, text);
}

}}