//=============
// WebServer.h
//=============

#pragma once


//=======
// Using
//=======

#include "Clusters/map.hpp"
#include "Network/Http/HttpServer.h"
#include "Network/Https/HttpsServer.h"
#include "WebContext.h"
#include "WebSession.h"


//===========
// Namespace
//===========

namespace Web {


//======================
// Forward-Declarations
//======================

class WebSite;


//============
// Web-Server
//============

class WebServer: public Object
{
public:
	// Using
	using HttpConnection=Network::Http::HttpConnection;
	using HttpServer=Network::Http::HttpServer;
	using HttpsServer=Network::Https::HttpsServer;
	using WebSessionMap=Clusters::map<Handle<String>, Handle<WebSession>>;

	// Con-/Destructors
	WebServer(WebSite* WebSite, Handle<String> HostName=nullptr);

	// Common
	VOID Listen();

private:
	// Common
	VOID DoAccept(Handle<HttpConnection> Connection);
	VOID DoGet(Handle<WebContext> Context);
	VOID DoNotify(Handle<WebContext> Context);
	VOID DoPost(Handle<WebContext> Context);
	VOID OnClockHour();
	VOID OnConnectionReceived(Handle<HttpConnection> Connection);
	Mutex cMutex;
	WebSessionMap cSessions;
	Handle<HttpServer> hHttpServer;
	Handle<HttpsServer> hHttpsServer;
	WebSite* pWebSite;
};

}