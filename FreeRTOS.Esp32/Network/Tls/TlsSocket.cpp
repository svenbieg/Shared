//===============
// TlsSocket.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <mbedtls/base64.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include "TlsCertificate.h"
#include "TlsKey.h"
#include "TlsRandom.h"
#include "TlsSocket.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tls {


//==================
// Con-/Destructors
//==================

TlsSocket::TlsSocket(Handle<TcpSocket> sock):
Socket(sock),
cConfig(),
cNetContext(),
cSslContext()
{
mbedtls_ssl_config_init(&cConfig);
mbedtls_net_init(&cNetContext);
mbedtls_ssl_init(&cSslContext);
cNetContext.fd=Socket->GetSocket();
}

TlsSocket::~TlsSocket()
{
CloseInternal();
}


//========
// Common
//========

BOOL TlsSocket::Accept(Handle<String> host_name)
{
auto cert=TlsCertificate::Store->Get(host_name);
auto key=TlsKey::Store->Get(host_name);
if(!cert||!key)
	{
	DebugPrint("TlsSocket::Accept() - No key-pair\n");
	return false;
	}
INT status=mbedtls_ssl_config_defaults(&cConfig, MBEDTLS_SSL_IS_SERVER, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT);
if(mbedtls_ssl_set_hostname(&cSslContext, host_name->Begin())!=0)
	{
	DebugPrint("TlsSocket::Accept() - mbedtls_ssl_set_hostname() failed (%i)\n", status);
	return false;
	}
auto random=TlsRandom::Get();
mbedtls_ssl_conf_rng(&cConfig, mbedtls_ctr_drbg_random, random->GetContext());
mbedtls_ssl_conf_ca_chain(&cConfig, cert->Get()->next, nullptr);
status=mbedtls_ssl_conf_own_cert(&cConfig, cert->Get(), key->Get());
if(status!=0)
	{
	DebugPrint("TlsSocket::Accept() - mbedtls_ssl_conf_own_cert() failed (%i)", status);
	return false;
	}
status=mbedtls_ssl_setup(&cSslContext, &cConfig);
if(status!=0)
	{
	DebugPrint("TlsSocket::Accept() - mbedtls_ssl_setup() failed (%i)", status);
	return false;
	}
mbedtls_ssl_set_bio(&cSslContext, &cNetContext, mbedtls_net_send, mbedtls_net_recv, nullptr);
while(1)
	{
	INT status=mbedtls_ssl_handshake(&cSslContext);
	if(status==0)
		break;
	if(status==MBEDTLS_ERR_SSL_WANT_READ)
		continue;
	if(status==MBEDTLS_ERR_SSL_WANT_WRITE)
		continue;
	DebugPrint("TlsSocket::Accept() - mbedtls_ssl_handshake() failed (%i)\n", status);
	return false;
	}
return true;
}

VOID TlsSocket::Close()
{
while(1)
	{
	INT status=mbedtls_ssl_close_notify(&cSslContext);
	if(status==0)
		break;
	if(status==MBEDTLS_ERR_SSL_WANT_READ)
		continue;
	if(status==MBEDTLS_ERR_SSL_WANT_WRITE)
		continue;
	DebugPrint("TlsSocket::Close() - mbedtls_ssl_close_notify() failed (%i)", status);
	break;
	}
CloseInternal();
}

BOOL TlsSocket::Handshake(Handle<String> host_name)
{
auto cert=TlsCertificate::Store->Get(host_name);
if(!cert)
	return false;
if(mbedtls_ssl_config_defaults(&cConfig, MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT)!=0)
	{
	DebugPrint("TlsSocket::Handshake() - mbedtls_ssl_config_defaults() failed\n");
	return false;
	}
auto random=TlsRandom::Get();
mbedtls_ssl_conf_authmode(&cConfig, MBEDTLS_SSL_VERIFY_REQUIRED);
mbedtls_ssl_conf_ca_chain(&cConfig, cert->Get(), nullptr);
mbedtls_ssl_conf_rng(&cConfig, mbedtls_ctr_drbg_random, random->GetContext());
if(mbedtls_ssl_setup(&cSslContext, &cConfig)!=0)
	{
	DebugPrint("TlsSocket::Handshake() - mbedtls_ssl_setup() failed\n");
	return false;
	}
mbedtls_ssl_set_bio(&cSslContext, &cNetContext, mbedtls_net_send, mbedtls_net_recv, nullptr);
while(1)
	{
	INT status=mbedtls_ssl_handshake(&cSslContext);
	if(status==0)
		break;
	if(status==MBEDTLS_ERR_SSL_WANT_READ)
		continue;
	if(status==MBEDTLS_ERR_SSL_WANT_WRITE)
		continue;
	DebugPrint("TlsSocket::Handshake() - mbedtls_ssl_handshake() failed (%i)\n", status);
	return false;
	}
if(mbedtls_ssl_get_verify_result(&cSslContext)!=0)
	{
	DebugPrint("TlsSocket::Handshake() - mbedtls_ssl_get_verify_result()\n");
	return false;
	}
return true;
}


//==============
// Input-Stream
//==============

SIZE_T TlsSocket::Available()
{
return mbedtls_ssl_get_bytes_avail(&cSslContext);
}

SIZE_T TlsSocket::Read(VOID* dstv, SIZE_T size)
{
auto dst=(BYTE*)dstv;
SIZE_T pos=0;
while(pos<size)
	{
	INT read=mbedtls_ssl_read(&cSslContext, &dst[pos], size-pos);
	if(read<=0)
		{
		if(read==MBEDTLS_ERR_SSL_WANT_READ)
			continue;
		if(read==MBEDTLS_ERR_SSL_WANT_WRITE)
			continue;
		throw std::exception();
		}
	pos+=read;
	}
return pos;
}


//===============
// Output-Stream
//===============

VOID TlsSocket::Flush()
{
}

SIZE_T TlsSocket::Write(VOID const* srcv, SIZE_T size)
{
auto src=(BYTE const*)srcv;
SIZE_T pos=0;
while(pos<size)
	{
	INT written=mbedtls_ssl_write(&cSslContext, &src[pos], size-pos);
	if(written<=0)
		{
		if(written==MBEDTLS_ERR_SSL_WANT_READ)
			continue;
		if(written==MBEDTLS_ERR_SSL_WANT_WRITE)
			continue;
		throw std::exception();
		}
	pos+=written;
	}
return pos;
}


//================
// Common Private
//================

VOID TlsSocket::CloseInternal()
{
mbedtls_ssl_free(&cSslContext);
mbedtls_ssl_config_free(&cConfig);
}

}}