//===============
// UdpSocket.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <lwip/sockets.h>
#include <lwip/udp.h>
#include <netdb.h>
#include "UdpSocket.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Udp {


//==================
// Con-/Destructors
//==================

UdpSocket::UdpSocket(INT sock):
iSocket(sock)
{}

UdpSocket::~UdpSocket()
{
Close();
}


//========
// Common
//========

BOOL UdpSocket::Broadcast(WORD port, VOID const* msg, WORD size)
{
udp_init();
udp_pcb* pcb=udp_new();
if(!pcb)
	{
	DebugPrint("UdpClient::Broadcast - udp_new() failed\n");
	return false;
	}
pbuf* pb=pbuf_alloc(PBUF_IP, size, PBUF_RAM);
if(!pb)
	{
	DebugPrint("UdpClient::Broadcast - pbuf_alloc() failed\n");
	return false;
	}
CopyMemory(pb->payload, msg, size);
ip_addr_t addr;
#ifdef ESP32
addr.type=IPADDR_TYPE_V4;
#endif
addr.IP4_UADDR=0xFFFFFFFF;
esp_err_t status=udp_sendto(pcb, pb, &addr, port);
pbuf_free(pb);
if(status!=ESP_OK)
	{
	DebugPrint("UdpClient::Broadcast - udp_sendto() failed\n");
	return false;
	}
return true;
}

VOID UdpSocket::Close()
{
if(iSocket!=-1)
	{
	shutdown(iSocket, SHUT_RDWR);
	closesocket(iSocket);
	iSocket=-1;
	}
}

BOOL UdpSocket::Listen(WORD port)
{
addrinfo addr;
ZeroMemory(&addr, sizeof(addr));
addr.ai_family=AF_INET;
addr.ai_socktype=SOCK_DGRAM;
addr.ai_protocol=IPPROTO_UDP;
addr.ai_flags=AI_PASSIVE;
addrinfo* paddr=nullptr;
CHAR pport[8];
StringPrint(pport, 8, "%u", port);
INT status=getaddrinfo(nullptr, pport, &addr, &paddr);
if(status!=0)
	return false;
INT sock=socket(paddr->ai_family, paddr->ai_socktype, paddr->ai_protocol);
if(sock<0)
	{
	freeaddrinfo(paddr);
	return false;
	}
status=bind(sock, paddr->ai_addr, (INT)paddr->ai_addrlen);
freeaddrinfo(paddr);
if(status!=0)
	{
	closesocket(sock);
	return false;
	}
iSocket=sock;
return true;
}

WORD UdpSocket::Read(VOID* buf, WORD size)
{
INT len=recv(iSocket, (CHAR*)buf, size, 0);
if(len<=0)
	throw std::exception();
return (WORD)len;
}

}}