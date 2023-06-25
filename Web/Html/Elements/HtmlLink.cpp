//==============
// HtmlLink.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "HtmlLink.h"
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

HtmlLink::HtmlLink(HtmlNode* parent, Handle<Sentence> link, Handle<Sentence> text):
HtmlNode(parent, "a"),
Link(link)
{
if(text)
	new HtmlText(this, text);
}


//==================
// Common Protected
//==================

SIZE_T HtmlLink::WriteAttributesToStream(OutputStream* stream, WebContext* context)
{
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print(" href=\"");
size+=writer.Print(Link->Begin(lng));
size+=writer.Print("\"");
return size;
}

}}