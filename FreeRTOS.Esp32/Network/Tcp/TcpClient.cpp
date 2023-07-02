//===============
// TcpClient.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <lwip/err.h>
#include <lwip/tcp.h>
#include <lwip/tcpip.h>
#include "TcpClient.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//==================
// Con-/Destructors
//==================

TcpClient::TcpClient():
pContext(nullptr),
uRemotePort(0),
uStatus(TcpClientStatus::Closed)
{}

TcpClient::~TcpClient()
{
CloseInternal();
}


//========
// Common
//========

VOID TcpClient::Close()
{
if(uStatus==TcpClientStatus::Closed)
	return;
CloseInternal();
Closed(this);
}

VOID TcpClient::Connect(UINT ip, WORD port)
{
Close();
DoConnect(ip, port);
}

VOID TcpClient::Connect(Handle<String> url, WORD port)
{
Close();
uRemotePort=port;
uStatus=TcpClientStatus::DnsLookup;
hDnsClient=new DnsClient();
hDnsClient->ServerFound.Add(this, &TcpClient::OnDnsClientServerFound);
hDnsClient->ServerNotFound.Add(this, &TcpClient::OnDnsClientServerNotFound);
hDnsClient->Lookup(url);
}


//===================
// Callbacks Private
//===================

ERR_T TcpClient::ConnectedProc(VOID* arg, VOID* pcb, ERR_T status)
{
Handle<TcpClient> client=(TcpClient*)arg;
return client->OnConnectedCallback(pcb, status);
}

VOID TcpClient::ErrorProc(VOID* arg, ERR_T err)
{
Handle<TcpClient> client=(TcpClient*)arg;
client->OnErrorCallback(err);
}

ERR_T TcpClient::OnConnectedCallback(VOID* pcb, ERR_T status)
{
uStatus=TcpClientStatus::Connected;
Handle<TcpConnection> con=new TcpConnection(pcb);
pContext=nullptr;
Connected(this, con);
return ERR_OK;
}

VOID TcpClient::OnErrorCallback(ERR_T err)
{
if(err==ERR_ABRT)
	pContext=nullptr;
Close();
}


//================
// Common Private
//================

VOID TcpClient::CloseInternal()
{
if(pContext)
	{
	tcp_pcb* pcb=(tcp_pcb*)pContext;
	tcp_err(pcb, nullptr);
	if(tcp_close(pcb)!=ERR_OK)
		tcp_abort(pcb);
	pContext=nullptr;
	}
hDnsClient=nullptr;
uRemotePort=0;
uStatus=TcpClientStatus::Closed;
}

VOID TcpClient::DoConnect(UINT ip, WORD port)
{
uStatus=TcpClientStatus::Connecting;
tcp_pcb* pcb=tcp_new();;
if(!pcb)
	{
	DebugPrint("TcpClient: tcp_new() failed\n");
	uStatus=TcpClientStatus::Closed;
	return;
	}
pContext=pcb;
/*pcb->so_options|=SOF_REUSEADDR;
if(tcp_bind(pcb, IP_ADDR_ANY, 0)!=ERR_OK)
	{
	DebugPrint("TcpClient - tcp_bind() failed\r\n");
	Close();
	return;
	}*/
ip_addr_t addr;
#ifdef ESP32
addr.type=IPADDR_TYPE_V4;
#endif
addr.IP4_UADDR=ip;
tcp_arg(pcb, this);
tcp_err(pcb, (tcp_err_fn)&ErrorProc);
err_t status=tcp_connect(pcb, &addr, port, (tcp_connected_fn)&ConnectedProc);
if(status!=ERR_OK)
	{
	DebugPrint("TcpClient: tcp_connect() failed (%i)\n", (INT)status);
	Close();
	}
}

VOID TcpClient::OnDnsClientServerFound(UINT ip)
{
hDnsClient=nullptr;
DoConnect(ip, uRemotePort);
}

VOID TcpClient::OnDnsClientServerNotFound()
{
hDnsClient=nullptr;
uStatus=TcpClientStatus::Closed;
ServerNotFound(this);
}

}}