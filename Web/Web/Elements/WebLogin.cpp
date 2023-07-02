//==============
// WebLogin.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "Resources/Strings/WebLogin.h"
#include "Storage/Streams/StringWriter.h"
#include "WebLogin.h"

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

WebLogin::WebLogin(HtmlNode* parent):
HtmlNode(parent, "div")
{
Class="login";
Document->AddStyle("div.login a", "color:inherit; font-weight:500; text-decoration:none");
Document->AddStyle("div.login a:visited", "color:inherit");
Document->AddStyle("div.login a:hover", "color:inherit");
}


//==================
// Common Protected
//==================

SIZE_T WebLogin::WriteElementsToStream(OutputStream* stream, WebContext* context, UINT level)
{
if(context->Url==LoginUrl)
	return 0;
auto lng=context->Language;
auto session=context->Session;
auto account=session->Account;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("\r\n");
size+=writer.PrintChar(' ', level*2);
if(account)
	{
	writer.Print(account->Name);
	}
else
	{
	size+=writer.Print("<a href=\"");
	size+=writer.Print(LoginUrl);
	size+=writer.Print("\">");
	size+=writer.Print(Translate(STR_WEB_LOGIN, lng));
	size+=writer.Print("</a>");
	}
return size;
}

}}