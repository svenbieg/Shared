//=============
// TcpServer.h
//=============

#pragma once


//=======
// Using
//=======

#include "Network/Tcp/TcpSocket.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//============
// Tcp-Server
//============

class TcpServer: public Object
{
public:
	// Con-/Destructors
	TcpServer();

	// Common
	Event<TcpServer, Handle<TcpSocket>> ConnectionReceived;
	VOID Listen(WORD Port);

private:
	// Common
	VOID DoListen();
	Handle<TcpSocket> hSocket;
};

}}
