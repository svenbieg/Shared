//=============
// TlsSocket.h
//=============

#pragma once


//=======
// Using
//=======

#include <mbedtls/net_sockets.h>
#include <mbedtls/ssl.h>
#include "Network/Tcp/TcpSocket.h"
#include "Storage/Streams/RandomAccessStream.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tls {


//============
// TLS-Socket
//============

class TlsSocket: public Storage::Streams::RandomAccessStream
{
public:
	// Using
	using TcpSocket=Network::Tcp::TcpSocket;

	// Con-/Destructors
	TlsSocket(Handle<TcpSocket> Socket);
	~TlsSocket();

	// Common
	BOOL Accept(Handle<String> HostName);
	VOID Close();
	BOOL Handshake(Handle<String> HostName);
	Handle<TcpSocket> Socket;

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	VOID CloseInternal();
	mbedtls_ssl_config cConfig;
	mbedtls_net_context cNetContext;
	mbedtls_ssl_context cSslContext;
};

}}