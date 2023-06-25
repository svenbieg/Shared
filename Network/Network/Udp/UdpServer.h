//=============
// UdpServer.h
//=============

#pragma once


//=======
// Using
//=======

#include "Network/Udp/UdpSocket.h"
#include "UdpMessage.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Udp {


//============
// UDP-Server
//============

class UdpServer: public Object
{
public:
	// Con-/Destructors
	UdpServer();

	// Common
	Event<UdpServer, Handle<UdpMessage>> MessageReceived;
	VOID Listen(WORD Port);

private:
	// Common
	VOID DoListen();
	Handle<UdpSocket> hSocket;
};

}}