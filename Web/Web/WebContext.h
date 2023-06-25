//==============
// WebContext.h
//==============

#pragma once


//=======
// Using
//=======

#include "Culture/Language.h"
#include "Network/Http/HttpConnection.h"
#include "Network/Http/HttpResponse.h"
#include "Storage/Directory.h"
#include "WebSession.h"


//===========
// Namespace
//===========

namespace Web {


//======================
// Forward-Declarations
//======================

class WebSite;


//=============
// Web-Context
//=============

class WebContext: public Object
{
public:
	// Using
	using Directory=Storage::Directory;
	using HttpConnection=Network::Http::HttpConnection;
	using HttpRequest=Network::Http::HttpRequest;
	using HttpResponse=Network::Http::HttpResponse;

	// Con-/Destructors
	WebContext(WebSite* WebSite);

	// Common
	Handle<HttpConnection> Connection;
	Handle<Directory> DocumentRoot;
	Handle<String> HostName;
	Culture::LanguageCode Language;
	LPCSTR Protocol;
	Handle<HttpRequest> Request;
	Handle<HttpResponse> Response;
	Handle<WebSession> Session;
	UINT64 TimeStamp;
	Handle<String> Url;
	Web::WebSite* const WebSite;
};

}