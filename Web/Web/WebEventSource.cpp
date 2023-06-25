//====================
// WebEventSource.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "Core/Application.h"
#include "Storage/Streams/StringWriter.h"
#include "Storage/DynamicBuffer.h"
#include "Web/Elements/WebVariable.h"
#include "WebEventSource.h"
#include "WebPage.h"

using namespace Core;
using namespace Network::Http;
using namespace Storage;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {


//=========
// Scripts
//=========

LPCSTR WebEventSourceScript=
"\r\n"
"function webPageUpdateElements(arg)\r\n"
"{\r\n"
"var params=arg.split(';');\r\n"
"params.forEach(function (param) {\r\n"
"\tif(param==\"\")\r\n"
"\t\treturn;\r\n"
"\tvar op=\"=\";\r\n"
"\tif(param.indexOf(\"+=\")>0)\r\n"
"\t\top=\"+=\";\r\n"
"\tvar pair=param.split(op);\r\n"
"\tvar key=pair[0];\r\n"
"\tvar value=pair[1];\r\n"
"\tvar element=document.getElementById(key);\r\n"
"\tif(element==null)\r\n"
"\t\treturn;\r\n"
"\tif(element.tagName.toLocaleLowerCase()=='input') {\r\n"
"\t\tvar edit=element;\r\n"
"\t\tif(op==\"=\")\r\n"
"\t\t\tedit.value=\"\";\r\n"
"\t\tedit.value+=value;\r\n"
"\t\treturn;\r\n"
"\t\t}\r\n"
"\tif(element.tagName.toLowerCase()=='table')\r\n"
"\t\telement=element.lastElementChild;\r\n"
"\tif(op==\"=\")\r\n"
"\t\telement.innerHTML=\"\";\r\n"
"\telement.innerHTML+=value;\r\n"
"\t});\r\n"
"}\r\n\r\n"
"\r\n"
"var event_source=new EventSource(window.location.href);\r\n"
"event_source.onmessage=function(e)\r\n"
"\t{\r\n"
"\twebPageUpdateElements(e.data);\r\n"
"\t}\r\n";


//==================
// Con-/Destructors
//==================

WebEventSource::WebEventSource(WebPage* page):
pWebPage(page),
uFlags(WebEventSourceFlags::None)
{
page->AddScript(WebEventSourceScript);
page->Changed.Add(this, &WebEventSource::OnPageChanged);
}

WebEventSource::~WebEventSource()
{
pWebPage->Changed.Remove(this);
}


//========
// Common
//========

VOID WebEventSource::RequestGet(Handle<WebContext> context)
{
ScopedLock lock(cMutex);
auto response=context->Response;
while(1)
	{
	if(GetFlag(uFlags, WebEventSourceFlags::Closing))
		{
		response->Status=HttpStatus::ConnectionClosed;
		return;
		}
	if(GetFlag(uFlags, WebEventSourceFlags::Event))
		{
		ClearFlag(uFlags, WebEventSourceFlags::Event);
		auto lng=context->Language;
		Handle<DynamicBuffer> buf=new DynamicBuffer();
		buf->SetFormat(StreamFormat::UTF8);
		StringWriter writer(buf);
		writer.Print("data: ");
		for(auto it=pWebPage->Controls->First(); it->HasCurrent(); it->MoveNext())
			{
			auto control=it->GetValue();
			auto var=dynamic_cast<WebVariable*>(control);
			if(!var)
				continue;
			var->UpdateToStream(buf, context);
			}
		writer.Print("\nretry: 0\n\n");
		buf->Seek(0);
		response->Properties->Set("Content-type", "text/event-stream; charset=utf-8");
		response->Content=buf;
		response->Status=HttpStatus::Ok;
		return;
		}
	SetFlag(uFlags, WebEventSourceFlags::Waiting);
	cSignal.Wait(lock);
	ClearFlag(uFlags, WebEventSourceFlags::Waiting);
	}
}


//================
// Common Private
//================

VOID WebEventSource::DoResponse()
{
cSignal.Broadcast();
}

VOID WebEventSource::OnPageChanged()
{
ScopedLock lock(cMutex);
if(!GetFlag(uFlags, WebEventSourceFlags::Event))
	{
	SetFlag(uFlags, WebEventSourceFlags::Event);
	Application::Current->Dispatch(this, &WebEventSource::DoResponse);
	}
}

}