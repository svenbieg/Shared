//===============
// TcpSocket.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <lwip/sockets.h>
#include <netdb.h>
#include "TcpSocket.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//==================
// Con-/Destructors
//==================

TcpSocket::TcpSocket(INT socket):
iSocket(socket)
{}

TcpSocket::~TcpSocket()
{
Close();
}


//========
// Common
//========

Handle<TcpSocket> TcpSocket::Accept()
{
INT sock=accept(iSocket, nullptr, nullptr);
if(sock<0)
	return nullptr;
return new TcpSocket(sock);
}

VOID TcpSocket::Close()
{
if(iSocket!=-1)
	{
	shutdown(iSocket, SHUT_RDWR);
	closesocket(iSocket);
	iSocket=-1;
	}
}

BOOL TcpSocket::Connect(Handle<String> host_name, WORD port)
{
LPCSTR host=host_name->Begin();
addrinfo info;
ZeroMemory(&info, sizeof(info));
info.ai_family=AF_INET;
info.ai_socktype=SOCK_STREAM;
addrinfo* result=nullptr;
getaddrinfo(host, nullptr, &info, &result);
if(!result)
	return false;
sockaddr_in addr=*(sockaddr_in*)(result->ai_addr);
freeaddrinfo(result);
INT sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if(sock<0)
	return false;
addr.sin_port=htons(port);
INT status=connect(sock, (sockaddr*)&addr, sizeof(sockaddr_in));
if(status!=0)
	{
	closesocket(sock);
	return false;
	}
iSocket=sock;
return true;
}

VOID TcpSocket::Listen(WORD port)
{
addrinfo addr;
ZeroMemory(&addr, sizeof(addr));
addr.ai_family=AF_INET;
addr.ai_socktype=SOCK_STREAM;
addr.ai_protocol=IPPROTO_TCP;
addr.ai_flags=AI_PASSIVE;
addrinfo* result=nullptr;
CHAR port_str[8];
StringPrint(port_str, 8, "%u", (UINT)port);
getaddrinfo(NULL, port_str, &addr, &result);
if(!result)
	{
	DebugPrint("TcpSocket::Listen() - getaddrinfo() failed\n");
	return;
	}
INT sock=socket(result->ai_family, result->ai_socktype, result->ai_protocol);
if(sock<0)
	{
	DebugPrint("TcpSocket::Listen() - socket() failed\n");
	freeaddrinfo(result);
	return;
	}
INT status=bind(sock, result->ai_addr, result->ai_addrlen);
freeaddrinfo(result);
if(status!=0)
	{
	DebugPrint("TcpSocket::Listen() - bind() failed\n");
	closesocket(sock);
	return;
	}
status=listen(sock, CONFIG_LWIP_MAX_SOCKETS);
if(status!=0)
	{
	DebugPrint("TcpSocket::Listen() - listen() failed\n");
	closesocket(sock);
	return;
	}
iSocket=sock;
}


//==============
// Input-Stream
//==============

SIZE_T TcpSocket::Available()
{
INT available=0;
if(ioctl(iSocket, FIONREAD, &available)!=0)
	return 0;
return available;
}

SIZE_T TcpSocket::Read(VOID* buf, SIZE_T size)
{
auto read=recv(iSocket, buf, size, 0);
if(read<0)
	throw std::exception();
return (SIZE_T)read;
}


//===============
// Output-Stream
//===============

VOID TcpSocket::Flush()
{
shutdown(iSocket, SHUT_WR);
}

SIZE_T TcpSocket::Write(VOID const* buf, SIZE_T size)
{
auto written=send(iSocket, buf, size, 0);
if(written<0)
	throw std::exception();
return (SIZE_T)written;
}

}}