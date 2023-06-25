//===============
// HtmlImage.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "HtmlImage.h"

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

HtmlImage::HtmlImage(HtmlNode* parent, Handle<Sentence> url):
HtmlNode(parent, "img"),
hUrl(url)
{}


//==================
// Common Protected
//==================

SIZE_T HtmlImage::WriteAttributesToStream(OutputStream* stream, WebContext* context)
{
auto lng=context->Language;
SIZE_T size=HtmlNode::WriteAttributesToStream(stream, context);
StringWriter writer(stream);
size+=writer.Print(" src=\"");
size+=writer.Print(hUrl->Begin(lng));
size+=writer.Print("\"");
return size;
}

}}