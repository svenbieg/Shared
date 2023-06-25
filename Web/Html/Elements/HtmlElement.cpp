//=================
// HtmlElement.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "HtmlNode.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//============================
// Con-/Destructors Protected
//============================

HtmlElement::HtmlElement(HtmlDocument* doc):
HtmlElement(doc, nullptr)
{}

HtmlElement::HtmlElement(HtmlNode* parent):
HtmlElement(parent->Document, parent)
{}

HtmlElement::HtmlElement(HtmlDocument* doc, HtmlNode* parent):
Document(doc),
Parent(parent)
{
if(Parent)
	{
	Parent->Elements->Append(this);
	Parent->SetFlag(HtmlNodeFlags::MultiLine);
	}
}

}}