//================
// TelnetServer.h
//================

#pragma once


//=======
// Using
//=======

#include "Network/Tcp/TcpSocket.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Telnet {


//===============
// Telnet-Server
//===============

class TelnetServer: public Object
{
public:
	// Using
	using TcpSocket=Network::Tcp::TcpSocket;

	// Con-/Destructors
	TelnetServer();

	// Common
	VOID Listen(WORD Port=22);

private:
	// Common
	VOID DoListen();
	Handle<TcpSocket> hSocket;
};

}}