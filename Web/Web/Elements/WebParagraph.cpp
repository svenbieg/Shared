//==================
// WebParagraph.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Html/Elements/HtmlCaption.h"
#include "Html/HtmlDocument.h"
#include "WebParagraph.h"

using namespace Html::Elements;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//==================
// Con-/Destructors
//==================

WebParagraph::WebParagraph(HtmlNode* parent, Handle<Sentence> caption):
HtmlNode(parent, "div")
{
Class="paragraph";
Document->AddStyle("div.paragraph", "padding-bottom:24px;");
if(caption)
	new HtmlCaption(this, caption);
}

}}