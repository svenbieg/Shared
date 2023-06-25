//=================
// HttpRequest.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamHelper.h"
#include "Storage/Streams/StringReader.h"
#include "Storage/Streams/StringWriter.h"
#include "HttpRequest.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//==================
// Con-/Destructors
//==================

HttpRequest::HttpRequest():
Method(HttpMethod::Get)
{
Cookies=new HttpParameters();
Parameters=new HttpParameters();
}


//========
// Common
//========

VOID HttpRequest::Clear()
{
HttpMessage::Clear();
Cookies->Clear();
Method=HttpMethod::Unknown;
Parameters->Clear();
Path=nullptr;
}

LanguageCode HttpRequest::GetLanguage()
{
auto lng=Parameters->Get("lng");
if(lng)
	return LanguageCodeFromString(lng->Begin());
lng=Properties->Get("Accept-Language");
if(!lng)
	return LanguageCode::None;
return LanguageCodeFromString(lng->Begin());
}

Handle<HttpRequest> HttpRequest::FromUrl(Handle<String> url)
{
Handle<HttpRequest> request=new HttpRequest();
if(!url)
	return request;
LPCTSTR url_ptr=url->Begin();
UINT host_pos=0;
if(StringCompare(url_ptr, "http://", 7, false)==0)
	host_pos+=7;
if(StringCompare(url_ptr, "https://", 8, false)==0)
	host_pos+=8;
Handle<String> host;
LPCTSTR host_ptr=&url_ptr[host_pos];
UINT path_pos=0;
if(StringFind(host_ptr, "/", &path_pos))
	{
	host=new String(path_pos, host_ptr);
	LPCTSTR path_ptr=&host_ptr[path_pos+1];
	UINT params_pos=0;
	if(StringFind(path_ptr, "?", &params_pos))
		{
		LPCTSTR params_ptr=&path_ptr[params_pos+1];
		request->Path=new String(params_pos, path_ptr);
		request->Parameters->Set(params_ptr);
		}
	else
		{
		request->Path=path_ptr;
		}
	}
else
	{
	host=host_ptr;
	}
request->Properties->Add("Host", host);
return request;
}

SIZE_T HttpRequest::ReadFromStream(InputStream* stream)
{
Clear();
Status=HttpStatus::InternalServerError;
StringReader reader(stream);
SIZE_T size=0;
TCHAR buf[256];
size+=reader.ReadString(buf, 256, " ");
Method=HttpMethodFromString(buf);
if(Method==HttpMethod::Unknown)
	return size;
UINT path_len=reader.ReadString(buf, 256, " ");
size+=path_len;
UINT params_pos=0;
if(StringFind(buf, "?", &params_pos))
	{
	Path=HttpPathToString(buf, params_pos);
	Parameters->Set(&buf[params_pos+1]);
	}
else
	{
	Path=HttpPathToString(buf, path_len);
	}
size+=reader.FindChar("\n");
while(1)
	{
	size+=reader.ReadString(buf, 256, "\r");
	size+=reader.Skip();
	if(buf[0]==0)
		break;
	UINT value_pos=0;
	if(!StringFind(buf, ":", &value_pos))
		{
		Properties->Add(buf, nullptr);
		continue;
		}
	buf[value_pos]=0;
	value_pos++;
	if(buf[value_pos]==' ')
		value_pos++;
	Handle<String> key=buf;
	Handle<String> value=&buf[value_pos];
	Properties->Add(key, value);
	}
auto cookie=Properties->Get("Cookie");
if(cookie)
	Cookies->Set(cookie->Begin());
Status=HttpStatus::Ok;
return size;
}

SIZE_T HttpRequest::WriteHeaderToStream(OutputStream* stream)
{
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print(HttpMethodToString(Method));
size+=writer.Print(" ");
size+=writer.Print(Path);
if(Parameters->GetCount()>0)
	{
	size+=writer.Print("?");
	size+=Parameters->WriteToStream(stream);
	}
size+=writer.Print(" HTTP/1.1\r\n");
for(auto it=Properties->First(); it->HasCurrent(); it->MoveNext())
	{
	auto key=it->GetKey();
	auto value=it->GetValue();
	size+=writer.Print(key);
	size+=writer.Print(": ");
	size+=writer.Print(value);
	size+=writer.Print("\r\n");
	}
size+=writer.Print("\r\n");
return size;
}

SIZE_T HttpRequest::WriteToStream(OutputStream* stream)
{
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print(HttpMethodToString(Method));
size+=writer.Print(" ");
size+=writer.Print(Path);
if(Parameters->GetCount()>0)
	{
	size+=writer.Print("?");
	size+=Parameters->WriteToStream(stream);
	}
size+=writer.Print(" HTTP/1.1\r\n");
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
	Properties->Add("Content-Type", "text/html; charset=ISO-8859-15");
	}
else
	{
	Properties->Remove("Content-Length");
	Properties->Remove("Content-Type");
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
size+=writer.Print("\r\n");
if(Content)
	size+=StreamCopy(stream, Content, (SIZE_T)content_size);
return size;
}

}}
