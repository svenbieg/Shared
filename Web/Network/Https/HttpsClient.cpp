//=================
// HttpsClient.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "HttpsClient.h"

using namespace Network::Http;
using namespace Network::Tcp;
using namespace Network::Tls;


//===========
// Namespace
//===========

namespace Network {
	namespace Https {


//========
// Common
//========

Handle<HttpConnection> HttpsClient::Connect(Handle<String> host_name, WORD port)
{
Handle<TcpSocket> tcp_sock=new TcpSocket();
if(!tcp_sock->Connect(host_name, port))
	return nullptr;
Handle<TlsSocket> tls_sock=new TlsSocket(tcp_sock);
if(!tls_sock->Handshake(host_name))
	return nullptr;
return new HttpConnection(tls_sock);
}

}}