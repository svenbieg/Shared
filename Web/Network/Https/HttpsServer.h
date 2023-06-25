//===============
// HttpsServer.h
//===============

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
// HTTPS-Server
//==============

class HttpsServer: public Object
{
private:
	// Using
	using HttpConnection=Network::Http::HttpConnection;
	using TcpSocket=Network::Tcp::TcpSocket;

public:
	// Con-/Destructors
	HttpsServer(Handle<String> HostName);

	// Common
	Event<HttpsServer, Handle<HttpConnection>> ConnectionReceived;
	VOID Listen(WORD Port=443);

private:
	// Common
	VOID DoListen();
	Handle<String> hHostName;
	Handle<Task> hListenTask;
	Handle<TcpSocket> hSocket;
};

}}
