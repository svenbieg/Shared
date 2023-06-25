//================
// HtmlColumn.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "HtmlTable.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//==================
// Con-/Destructors
//==================

HtmlColumn::HtmlColumn(HtmlTable* table, LPCSTR style):
Style(style)
{
table->Columns->Add(this);
}


//========
// Common
//========

SIZE_T HtmlColumn::WriteToStream(OutputStream* stream, UINT level)
{
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("\r\n");
size+=writer.PrintChar(' ', level*2);
size+=writer.Print("<col ");
if(Style)
	{
	size+=writer.Print("style=\"");
	size+=writer.Print(Style);
	size+=writer.Print("\"");
	}
size+=writer.Print("/>");
return size;
}

}}}