//=================
// HttpResonse.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamHelper.h"
#include "Storage/Streams/StringReader.h"
#include "Storage/Streams/StringWriter.h"
#include "HttpResponse.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//==================
// Con-/Destructors
//==================

HttpResponse::HttpResponse(HttpStatus status):
HttpMessage(status)
{
Cookies=new HttpParameters();
Properties->Set("Connection", "Close");
}


//========
// Common
//========

VOID HttpResponse::Clear()
{
HttpMessage::Clear();
Cookies->Clear();
}

SIZE_T HttpResponse::ReadFromStream(InputStream* stream)
{
Clear();
StringReader reader(stream);
SIZE_T size=0;
TCHAR buf[256];
size+=reader.ReadString(buf, 256, "\r");
UINT ver0=0;
UINT ver1=0;
UINT status=0;
if(StringScan(buf, "HTTP/%u.%u %u", &ver0, &ver1, &status)!=3)
	{
	Status=HttpStatus::InternalServerError;
	return size;
	}
Status=(HttpStatus)status;
size+=reader.Skip();
while(1)
	{
	size+=reader.ReadString(buf, 256, "\r");
	size+=reader.Skip();
	if(buf[0]==0)
		break;
	UINT value_pos=0;
	if(!StringFind(buf, ":", &value_pos))
		{
		Status=HttpStatus::InternalServerError;
		return size;
		}
	buf[value_pos]=0;
	value_pos++;
	if(buf[value_pos]==' ')
		value_pos++;
	Handle<String> key=buf;
	Handle<String> value=&buf[value_pos];
	Properties->Add(key, value);
	}
auto set_cookie=Properties->Get("Set-Cookie");
if(set_cookie)
	{
	Cookies->Set(set_cookie->Begin());
	Properties->Remove("Set-Cookie");
	}
return size;
}

SIZE_T HttpResponse::WriteHeaderToStream(OutputStream* stream)
{
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("HTTP/1.1 %u %s\r\n", (UINT)Status, HttpStatusToString(Status));
for(auto it=Properties->First(); it->HasCurrent(); it->MoveNext())
	{
	auto key=it->GetKey();
	auto value=it->GetValue();
	size+=writer.Print(key);
	size+=writer.Print(": ");
	size+=writer.Print(value);
	size+=writer.Print("\r\n");
	}
if(Cookies->GetCount()>0)
	{
	size+=writer.Print("Set-Cookie: ");
	for(auto it=Cookies->First(); it->HasCurrent(); it->MoveNext())
		{
		auto key=it->GetKey();
		auto value=it->GetValue();
		writer.Print(key);
		writer.Print("=");
		writer.Print(value);
		writer.Print(";");
		}
	writer.Print("\r\n");
	}
size+=writer.Print("\r\n");
return size;
}

SIZE_T HttpResponse::WriteToStream(OutputStream* stream)
{
Properties->Add("Content-Type", "text/html; charset=utf-8");
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("HTTP/1.1 %u %s\r\n", (UINT)Status, HttpStatusToString(Status));
UINT64 content_size=0;
Handle<String> content_len;
if(Content)
	{
	content_len=Properties->Get("Content-Length");
	if(content_len)
		{
		StringScan(content_len->Begin(), "%u", &content_size);
		}
	else
		{
		content_size=Content->GetSize();
		}
	if(content_size>SIZE_MAX)
		content_size=0;
	}
if(content_size>0)
	{
	if(!content_len)
		Properties->Add("Content-Length", new String("%u", content_size));
	Properties->Add("Cache-Control", "no-cache");
	}
else
	{
	Properties->Remove("Content-Length");
	}
for(auto it=Properties->First(); it->HasCurrent(); it->MoveNext())
	{
	auto key=it->GetKey();
	auto value=it->GetValue();
	size+=writer.Print(key);
	size+=writer.Print(": ");
	size+=writer.Print(value);
	size+=writer.Print("\r\n");
	}
if(Cookies->GetCount()>0)
	{
	size+=writer.Print("Set-Cookie: ");
	for(auto it=Cookies->First(); it->HasCurrent(); it->MoveNext())
		{
		auto key=it->GetKey();
		auto value=it->GetValue();
		writer.Print(key);
		writer.Print("=");
		writer.Print(value);
		writer.Print(";");
		}
	writer.Print("\r\n");
	}
size+=writer.Print("\r\n");
if(Content)
	size+=StreamCopy(stream, Content, (SIZE_T)content_size);
return size;
}

}}