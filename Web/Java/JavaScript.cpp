//================
// JavaScript.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "Storage/Streams/StringWriter.h"
#include "Web/WebContext.h"
#include "JavaScript.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Java {


//==================
// Con-/Destructors
//==================

JavaScript::JavaScript()
{}


//========
// Common
//========

VOID JavaScript::Add(LPCSTR global)
{
if(!hGlobals)
	hGlobals=new GlobalsList();
hGlobals->Add(global);
}

VOID JavaScript::Add(Handle<JavaFunction> func)
{
if(!hFunctions)
	hFunctions=new JavaFunctionList();
hFunctions->Add(func);
}

SIZE_T JavaScript::WriteToStream(OutputStream* stream, WebContext* context)
{
if(!hGlobals&&!hFunctions)
	return 0;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("\r\n<script type=\"text/javascript\">\r\n");
for(auto it=hGlobals->First(); it->HasCurrent(); it->MoveNext())
	{
	auto global=it->GetCurrent();
	size+=writer.Print(global);
	}
for(auto it=hFunctions->First(); it->HasCurrent(); it->MoveNext())
	{
	auto func=it->GetCurrent();
	size+=func->Run(stream, context);
	}
size+=writer.Print("</script>\r\n\r\n");
return size;
}

}