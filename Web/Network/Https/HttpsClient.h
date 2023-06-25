//==============
// HttpClient.h
//==============

#pragma once


//=======
// Using
//=======

#include "Network/Http/HttpConnection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Https {


//==============
// HTTPS-Client
//==============

class HttpsClient
{
public:
	// Using
	using HttpConnection=Network::Http::HttpConnection;

	// Common
	static Handle<HttpConnection> Connect(Handle<String> HostName, WORD Port=443);
};

}}