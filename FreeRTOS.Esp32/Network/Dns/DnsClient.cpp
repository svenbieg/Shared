//===============
// DnsClient.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <lwip/dns.h>
#include "Core/Application.h"
#include "DnsClient.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Network {
	namespace Dns {


//==================
// Con-/Destructors
//==================

DnsClient::DnsClient():
uIp(0)
{}


//========
// Common
//========

VOID DnsClient::Lookup(Handle<String> server)
{
ip_addr_t ip;
err_t status=dns_gethostbyname(server->Begin(), &ip, (dns_found_callback)&DnsNameFoundProc, this);
if(status==ERR_INPROGRESS)
	{
	hCallback=this;
	return;
	}
if(status!=ERR_OK)
	{
	ServerNotFound(this);
	return;
	}
ServerFound(this, ip.IP4_UADDR);
}


//================
// Common Private
//================

VOID DnsClient::DnsNameFoundProc(LPCSTR name, VOID const* addr, VOID* arg)
{
auto client=(DnsClient*)arg;
client->OnDnsNameFound(name, addr);
}

VOID DnsClient::OnDnsNameFound(LPCSTR name, VOID const* addr)
{
UINT ip=0;
ip_addr_t* pip=(ip_addr_t*)addr;
if(pip)
	ip=pip->IP4_UADDR;
Application::Current->Dispatch(this, &DnsClient::OnServerFound, ip);
}

VOID DnsClient::OnServerFound(UINT ip)
{
ip? ServerFound(this, ip): ServerNotFound(this);
hCallback=nullptr;
}

}}