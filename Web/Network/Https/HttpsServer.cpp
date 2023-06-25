//=================
// HttpsServer.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "HttpsServer.h"

using namespace Network::Tls;


//===========
// Namespace
//===========

namespace Network {
	namespace Https {


//==================
// Con-/Destructors
//==================

HttpsServer::HttpsServer(Handle<String> host_name):
hHostName(host_name)
{}


//========
// Common
//========

VOID HttpsServer::Listen(WORD port)
{
hSocket=new TcpSocket();
hSocket->Listen(port);
hListenTask=CreateTask(this, &HttpsServer::DoListen);
}


//================
// Common Private
//================

VOID HttpsServer::DoListen()
{
auto task=GetCurrentTask();
while(!task->Cancelled)
	{
	Handle<TcpSocket> tcp_sock=hSocket->Accept();
	if(!tcp_sock)
		break;
	Handle<TlsSocket> tls_sock=new TlsSocket(tcp_sock);
	if(!tls_sock->Accept(hHostName))
		break;
	Handle<HttpConnection> http_con=new HttpConnection(tls_sock);
	ConnectionReceived(this, http_con);
	}
}

}}