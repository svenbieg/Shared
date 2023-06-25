//==============
// WebInput.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "Storage/Streams/StringWriter.h"
#include "Web/WebPage.h"
#include "Url.h"
#include "WebInput.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//=========
// Scripts
//=========

LPCSTR WebInputScript=
"\r\n"
"function webInputChanged(id, value)\r\n"
"{\r\n"
"var request=new XMLHttpRequest();\r\n"
"request.open('NOTIFY', '?id='+id+'&value='+encodeURIComponent(value));\r\n"
"request.send();\r\n"
"}\r\n";


//==================
// Con-/Destructors
//==================

WebInput::WebInput(HtmlNode* parent, Handle<Variable> var, Handle<String> id, WebInputType type):
WebVariable(parent, "input", id? id: var->Name),
hVariable(var),
uInputType(type),
uTimeChanged(0)
{
hVariable->Changed.Add(this, &WebInput::OnVariableChanged);
Document->AddScript(WebInputScript);
Document->AddStyle("input", "margin-top:8px; padding-left:2px; padding-right:2px; width:200px");
if(uInputType==WebInputType::Number)
	{
	Document->AddStyle("input.num", "width:50px");
	Class="num";
	}
}

WebInput::~WebInput()
{
hVariable->Changed.Remove(this);
}


//========
// Common
//========

VOID WebInput::OnNotified(Handle<WebContext> context)
{
auto request=context->Request;
auto value=request->Parameters->Get("value");
value=Url::Decode(value);
hVariable->FromString(value);
}

SIZE_T WebInput::UpdateToStream(OutputStream* stream, WebContext* context)
{
if(context->TimeStamp>uTimeChanged)
	return 0;
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print(Id);
size+=writer.Print("=");
size+=writer.Print(hVariable->ToString(lng));
size+=writer.Print(";");
return size;
}


//==================
// Common Protected
//==================

SIZE_T WebInput::WriteAttributesToStream(OutputStream* stream, WebContext* context)
{
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=WebVariable::WriteAttributesToStream(stream, context);
if(uInputType!=WebInputType::Text)
	{
	size+=writer.Print(" type=\"");
	switch(uInputType)
		{
		default:
		case WebInputType::Number:
			{
			size+=writer.Print("number");
			break;
			}
		case WebInputType::Password:
			{
			size+=writer.Print("password");
			break;
			}
		}
	size+=writer.Print("\"");
	}
size+=writer.Print(" value=\"");
size+=writer.Print(hVariable->ToString(lng));
size+=writer.Print("\" onchange=\"webInputChanged('");
size+=writer.Print(Id);
size+=writer.Print("', this.value)\"");
return size;
}


//================
// Common Private
//================

VOID WebInput::OnVariableChanged()
{
uTimeChanged=GetTickCount64();
Page->Changed(Page);
}

}}