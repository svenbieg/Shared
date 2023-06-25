//==================
// HttpConnection.h
//==================

#pragma once


//=======
// Using
//=======

#include "Network/Tcp/TcpSocket.h"
#include "Network/Tls/TlsSocket.h"
#include "Storage/File.h"
#include "HttpResponse.h"
#include "HttpRequest.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=======
// Flags
//=======

enum class HttpConnectionFlags: UINT
{
None=0,
Protected=1
};


//=================
// HTTP-Connection
//=================

class HttpConnection: public Storage::Streams::RandomAccessStream
{
public:
	// Using
	using File=Storage::File;
	using TcpSocket=Network::Tcp::TcpSocket;
	using TlsSocket=Network::Tls::TlsSocket;

	// Con-/Destructors
	HttpConnection(Handle<TcpSocket> Socket);
	HttpConnection(Handle<TlsSocket> Socket);

	// Common
	Handle<HttpRequest> GetRequest();
	Handle<HttpResponse> GetResponse();
	BOOL IsProtected()const { return GetFlag(uFlags, HttpConnectionFlags::Protected); }
	VOID Send(Handle<HttpRequest> Request);
	VOID Send(Handle<HttpResponse> Response);
	BOOL SendFile(Handle<File> File, Handle<String> Path=nullptr);
	Handle<TcpSocket> Socket;

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	Handle<Object> hSocket;
	RandomAccessStream* pStream;
	HttpConnectionFlags uFlags;
};

}}
