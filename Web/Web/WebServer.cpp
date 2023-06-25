//===============
// WebServer.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Clock.h"
#include "Devices/Random.h"
#include "Storage/Streams/StreamHelper.h"
#include "Storage/Buffer.h"
#include "Web/Security/GoogleToken.h"
#include "WebPage.h"
#include "WebServer.h"
#include "WebSite.h"

using namespace Devices;
using namespace Network::Http;
using namespace Storage;
using namespace Storage::Streams;
using namespace Web::Security;


//===========
// Namespace
//===========

namespace Web {


//==================
// Con-/Destructors
//==================

WebServer::WebServer(WebSite* web_site, Handle<String> host_name):
pWebSite(web_site)
{
hHttpServer=new HttpServer();
hHttpServer->ConnectionReceived.Add(this, &WebServer::OnConnectionReceived);
if(host_name)
	{
	hHttpsServer=new HttpsServer(host_name);
	hHttpsServer->ConnectionReceived.Add(this, &WebServer::OnConnectionReceived);
	}
auto clock=Clock::Get();
clock->Hour.Add(this, &WebServer::OnClockHour);
}


//========
// Common
//========

VOID WebServer::Listen()
{
hHttpServer->Listen();
if(hHttpsServer)
	hHttpsServer->Listen();
}


//================
// Common Private
//================

VOID WebServer::DoAccept(Handle<HttpConnection> con)
{
auto request=con->GetRequest();
auto sid=request->Cookies->Get("sid");
ScopedLock lock(cMutex);
Handle<WebSession> session;
if(!cSessions.try_get(sid, &session))
	{
	while(1)
		{
		sid=RandomString(16);
		if(!cSessions.contains(sid))
			break;
		}
	session=new WebSession(sid);
	cSessions.set(sid, session);
	}
lock.Unlock();
Handle<HttpResponse> response=new HttpResponse(HttpStatus::BadRequest);
response->Cookies->Set("sid", sid);
auto host_name=request->Properties->Get("Host");
if(!host_name)
	return;
ScopedLock session_lock(session->CriticalSection);
auto doc_root=pWebSite->Public;
if(con->IsProtected())
	{
	doc_root=pWebSite->Protected;
	auto account=session->Account;
	if(account)
		doc_root=account->DocumentRoot;
	}
else
	{
	session->Account=nullptr;
	}
session->TimeOut=GetTickCount64()+60*60*1000;
session_lock.Unlock();
Handle<WebContext> context=new WebContext(pWebSite);
context->Connection=con;
context->DocumentRoot=doc_root;
context->HostName=host_name;
context->Language=request->GetLanguage();
context->Protocol=con->IsProtected()? "https": "http";
context->Request=request;
context->Response=response;
context->Session=session;
context->TimeStamp=GetTickCount64();
context->Url=new String("%s://%s%s", context->Protocol, context->HostName, request->Path);
switch(request->Method)
	{
	case HttpMethod::Get:
		{
		DoGet(context);
		break;
		}
	case HttpMethod::Notify:
		{
		DoNotify(context);
		break;
		}
	case HttpMethod::Post:
		{
		DoPost(context);
		break;
		}
	default:
		break;
	}
con->Send(response);
}

VOID WebServer::DoGet(Handle<WebContext> context)
{
auto request=context->Request;
auto response=context->Response;
auto path=request->Path;
if(path=="/"||path=="/gen_204")
	{
	Handle<String> url=new String("%s://%s/index.html", context->Protocol, context->HostName);
	response->Status=HttpStatus::MovedPermanently;
	response->Properties->Add("Location", url);
	return;
	}
auto doc_root=context->DocumentRoot;
Handle<Object> obj=doc_root->Get(path);
if(!obj)
	{
	response->Status=HttpStatus::SiteNotFound;
	return;
	}
auto web_page=Convert<WebPage>(obj);
if(web_page)
	{
	web_page->RequestGet(context);
	return;
	}
auto file=Convert<File>(obj);
if(file)
	{
	if(Failed(file->Create(FileCreateMode::OpenExisting, FileAccessMode::ReadOnly, FileShareMode::ShareRead)))
		{
		response->Status=HttpStatus::InternalServerError;
		return;
		}
	auto file_name=file->GetName();
	UINT64 file_size=file->GetSize();
	response->Content=file;
	response->Properties->Set("Content-Disposition", new String("attachment; filename=%s", file_name->Begin()));
	response->Properties->Set("Content-Length", new String("%u", file_size));
	response->Status=HttpStatus::Ok;
	return;
	}
}

VOID WebServer::DoNotify(Handle<WebContext> context)
{
auto request=context->Request;
auto response=context->Response;
auto path=request->Path;
auto doc_root=context->DocumentRoot;
auto web_page=Convert<WebPage>(doc_root->Get(path));
if(!web_page)
	{
	response->Status=HttpStatus::SiteNotFound;
	return;
	}
web_page->RequestNotify(context);
}

VOID WebServer::DoPost(Handle<WebContext> context)
{
auto request=context->Request;
auto path=request->Path;
auto doc_root=context->DocumentRoot;
auto obj=doc_root->Get(path);
auto web_page=Convert<WebPage>(obj);
if(web_page)
	{
	web_page->RequestPost(context);
	return;
	}
auto response=context->Response;
while(1)
	{
	auto range=request->Properties->Get("Content-Range");
	if(!range)
		return;
	UINT64 file_start=0;
	UINT64 file_end=0;
	UINT64 file_size=0;
	if(range->Scan("%u-%u/%u", &file_start, &file_end, &file_size)!=3)
		return;
	Handle<File> file;
	if(file_start==0)
		{
		Handle<String> name=request->Parameters->Get("name");
		Handle<String> path=new String("%s/%s", request->Path, name);
		file=doc_root->CreateFile(path, FileCreateMode::CreateAlways, FileAccessMode::ReadWrite, FileShareMode::ShareRead);
		if(file)
			{
			if(!file->SetSize(file_size))
				file=nullptr;
			}
		}
	if(!file)
		{
		response->Status=HttpStatus::InternalServerError;
		return;
		}
	auto con=context->Connection;
	SIZE_T copy=(SIZE_T)(file_end-file_start);
	SIZE_T written=StreamCopy(file, con, copy);
	if(written!=copy)
		{
		file=nullptr;
		response->Status=HttpStatus::InternalServerError;
		return;
		}
	response->Status=HttpStatus::Ok;
	file_start+=written;
	if(file_start>=file_size)
		{
		file->Flush();
		file=nullptr;
		return;
		}
	response->KeepAlive(true);
	con->Send(response);
	request=con->GetRequest();
	}
}

VOID WebServer::OnClockHour()
{
ScopedLock lock(cMutex);
auto time=GetTickCount64();
for(auto it=cSessions.begin(); it.has_current();)
	{
	auto item=it.get_current();
	auto session=item.get_value();
	if(session->TimeOut<time)
		{
		it.remove_current();
		continue;
		}
	it.move_next();
	}
}

VOID WebServer::OnConnectionReceived(Handle<HttpConnection> con)
{
CreateTask(this, &WebServer::DoAccept, con);
}

}