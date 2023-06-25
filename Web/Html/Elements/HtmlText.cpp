//==============
// HtmlText.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "HtmlText.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//==================
// Con-/Destructors
//==================

HtmlText::HtmlText(HtmlNode* parent, Handle<Sentence> text):
HtmlElement(parent),
hText(text)
{}


//========
// Common
//========

SIZE_T HtmlText::WriteToStream(OutputStream* stream, WebContext* context, UINT level)
{
StringWriter writer(stream);
return writer.Print(hText->Begin(context->Language));
}

}}