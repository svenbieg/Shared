//===========
// WebSite.h
//===========

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Network/Http/HttpConnection.h"
#include "Storage/Workspace.h"
#include "WebAccount.h"
#include "WebServer.h"


//===========
// Namespace
//===========

namespace Web {


//==========
// Web-Site
//==========

class WebSite: public Object
{
public:
	// Using
	using HttpConnection=Network::Http::HttpConnection;
	using WebAccountMap=Collections::Map<Handle<String>, Handle<WebAccount>>;
	using Workspace=Storage::Workspace;

	// Con-/Destructors
	WebSite(Handle<String> HostName=nullptr);

	// Common
	Handle<WebAccountMap> Accounts;
	static Handle<WebSite> Current;
	Handle<Workspace> Protected;
	Handle<Workspace> Public;

private:
	// Common
	Handle<WebServer> hWebServer;
};

}