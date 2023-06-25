//===============
// HtmlLabel.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "HtmlLabel.h"

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

HtmlLabel::HtmlLabel(HtmlNode* parent, Handle<Sentence> label, Handle<Sentence> unit):
HtmlNode(parent, "label"),
Label(label),
Unit(unit)
{}


//==================
// Common Protected
//==================

SIZE_T HtmlLabel::WriteElementsToStream(OutputStream* stream, WebContext* context, UINT level)
{
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
if(Label)
	{
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', level*2);
	size+=writer.Print(Label->Begin(lng));
	}
size+=HtmlNode::WriteElementsToStream(stream, context, level);
if(Unit)
	{
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', level*2);
	size+=writer.Print(Unit->Begin(lng));
	}
return size;
}

}}