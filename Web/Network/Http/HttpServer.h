//==============
// HttpServer.h
//==============

#pragma once


//=======
// Using
//=======

#include "Network/Tcp/TcpSocket.h"
#include "HttpConnection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=============
// HTTP-Server
//=============

class HttpServer: public Object
{
private:
	// Using
	using TcpSocket=Network::Tcp::TcpSocket;

public:
	// Con-/Destructors
	HttpServer();

	// Common
	Event<HttpServer, Handle<HttpConnection>> ConnectionReceived;
	VOID Listen(WORD Port=80);

private:
	// Common
	VOID DoListen();
	Handle<Task> hListenTask;
	Handle<TcpSocket> hSocket;
};

}}
