//==================
// HtmlDocument.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "HtmlDocument.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {


//==================
// Con-/Destructors
//==================

HtmlDocument::HtmlDocument():
HtmlElement(this)
{
Head=new HtmlHead(this);
Body=new HtmlNode(this, "body");
}


//========
// Common
//========

SIZE_T HtmlDocument::WriteToStream(OutputStream* stream, WebContext* context, UINT level)
{
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("<!DOCTYPE html>\r\n\r\n");
size+=writer.Print("<html lang=\"");
size+=writer.Print(LanguageCodeToString(lng));
size+=writer.Print("\">\r\n\r\n");
size+=Head->WriteToStream(stream, context, 0);
size+=Body->WriteToStream(stream, context, 0);
size+=writer.Print("\r\n</html>\r\n");
return size;
}

}