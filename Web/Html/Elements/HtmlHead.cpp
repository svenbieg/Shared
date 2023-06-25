//==============
// HtmlHead.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "HtmlHead.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//==================
// Con-/Destructors
//==================

HtmlHead::HtmlHead(HtmlDocument* doc):
HtmlNode(doc, "head"),
Icon(nullptr)
{
Script=new JavaScript();
Styles=new StyleList();
SetFlag(HtmlNodeFlags::MultiLine);
}


//========
// Common
//========

SIZE_T HtmlHead::WriteToStream(OutputStream* stream, WebContext* context, UINT level)
{
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("<head>\r\n");
if(Title)
	{
	size+=writer.Print("<title>");
	size+=writer.Print(Title->Begin(lng));
	size+=writer.Print("</title>\r\n");
	}
if(Icon)
	{
	size+=writer.Print("<link rel=\"icon\" type=\"image/x-icon\" href=\"");
	size+=writer.Print(Icon);
	size+=writer.Print("\">\r\n");
	}
size+=writer.Print("<meta charset=\"UTF-8\">\r\n");
size+=writer.Print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\r\n");
size+=WriteElementsToStream(stream, context, level);
if(Styles->GetCount()>0)
	{
	size+=writer.Print("\r\n<style type=\"text/css\">\r\n");
	for(auto it=Styles->First(); it->HasCurrent(); it->MoveNext())
		{
		auto id=it->GetKey();
		auto style=it->GetValue();
		size+=writer.Print(id);
		size+=writer.Print(" { ");
		size+=writer.Print(style);
		size+=writer.Print(" }\r\n");
		}
	size+=writer.Print("</style>\r\n\r\n");
	}
size+=Script->WriteToStream(stream, context);
size+=writer.Print("</head>\r\n\r\n");
return size;
}

}}