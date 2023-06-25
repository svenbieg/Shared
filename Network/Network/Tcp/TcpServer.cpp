//===============
// TcpServer.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "TcpServer.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//==================
// Con-/Destructors
//==================

TcpServer::TcpServer()
{}


//========
// Common
//========

VOID TcpServer::Listen(WORD port)
{
hSocket=new TcpSocket();
hSocket->Listen(port);
CreateTask(this, &TcpServer::DoListen);
}


//================
// Common Private
//================

VOID TcpServer::DoListen()
{
while(1)
	{
	Handle<TcpSocket> tcp_sock=hSocket->Accept();
	if(!tcp_sock)
		break;
	ConnectionReceived(this, tcp_sock);
	}
}

}}