//================
// HttpClient.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Network/Tcp/TcpSocket.h"
#include "Storage/Buffer.h"
#include "HttpClient.h"

using namespace Network::Tcp;
using namespace Storage;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//========
// Common
//========

Handle<HttpConnection> HttpClient::Connect(Handle<String> host, WORD port)
{
Handle<TcpSocket> sock=new TcpSocket();
if(!sock->Connect(host, port))
	return nullptr;
return new HttpConnection(sock);
}

}}