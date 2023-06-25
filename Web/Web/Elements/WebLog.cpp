//============
// WebLog.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "Resources/Strings/WebLog.h"
#include "Storage/Streams/StringWriter.h"
#include "Web/WebPage.h"
#include "WebLog.h"

using namespace Collections;
using namespace Culture;
using namespace Physics;
using namespace Resources::Strings;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//==================
// Con-/Destructors
//==================

WebLog::WebLog(HtmlNode* parent, Handle<String> id, Handle<Log> log):
WebVariable(parent, "table", id),
hLog(log),
uTimeChanged(0)
{
Class="logbox";
Document->AddStyle("table.logbox td", "vertical-align:top;");
Document->AddStyle("table.logbox th", "padding-right:8px; text-align:right; vertical-align:top;");
auto btn=new WebButton(parent, id+"Button", STR_WEB_LOG_CLEAR);
btn->Clicked.Add(this, &WebLog::OnClearButtonClicked);
hLog->Changed.Add(this, &WebLog::OnLogChanged);
}

WebLog::~WebLog()
{
hLog->Changed.Remove(this);
}


//========
// Common
//========

SIZE_T WebLog::UpdateToStream(OutputStream* stream, WebContext* context)
{
if(context->TimeStamp>uTimeChanged)
	return 0;
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print(Id);
size+=writer.Print("=");
for(auto it=hLog->Entries->First(); it->HasCurrent(); it->MoveNext())
	{
	auto entry=it->GetCurrent();
	size+=writer.Print("<tr><th>");
	size+=writer.Print(entry->Time->ToString(TimeFormat::DateTime, lng));
	size+=writer.Print("</th><td>");
	size+=writer.Print(entry->Message->Begin(lng));
	size+=writer.Print("</td></tr>");
	}
size+=writer.Print(";");
return size;
}

SIZE_T WebLog::WriteToStream(OutputStream* stream, WebContext* context, UINT level)
{
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=WriteTagToStream(stream, level);
size+=WriteAttributesToStream(stream, context);
size+=writer.Print(">\r\n");
UINT body_level=level+1;
size+=writer.PrintChar(' ', body_level*2);
size+=writer.Print("<tbody>");
UINT row_level=body_level+1;
for(auto it=hLog->Entries->First(); it->HasCurrent(); it->MoveNext())
	{
	auto entry=it->GetCurrent();
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', row_level*2);
	size+=writer.Print("<tr><th>");
	size+=writer.Print(entry->Time->ToString(TimeFormat::DateTime, lng));
	size+=writer.Print("</th><td>");
	size+=writer.Print(entry->Message->Begin(lng));
	size+=writer.Print("</td></tr>");
	}
size+=writer.Print("\r\n");
size+=writer.PrintChar(' ', body_level*2);
size+=writer.Print("</tbody>\r\n");
size+=writer.PrintChar(' ', level*2);
size+=writer.Print("</table><br />");
return size;
}


//================
// Common Private
//================

VOID WebLog::OnClearButtonClicked()
{
hLog->Clear();
hLog->Write(STR_WEB_LOG_CLEARED);
}

VOID WebLog::OnLogChanged()
{
uTimeChanged=GetTickCount64();
Page->Changed(Page);
}

}}