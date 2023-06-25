//====================
// HttpConnection.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "HttpConnection.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//==================
// Con-/Destructors
//==================

HttpConnection::HttpConnection(Handle<TcpSocket> sock):
Socket(sock),
hSocket(sock),
pStream(sock),
uFlags(HttpConnectionFlags::None)
{
uFormat=StreamFormat::Ansi;
}

HttpConnection::HttpConnection(Handle<TlsSocket> sock):
Socket(sock->Socket),
hSocket(sock),
pStream(sock),
uFlags(HttpConnectionFlags::Protected)
{
uFormat=StreamFormat::Ansi;
}


//========
// Common
//========

Handle<HttpRequest> HttpConnection::GetRequest()
{
Handle<HttpRequest> request=new HttpRequest();
request->ReadFromStream(this);
return request;
}

Handle<HttpResponse> HttpConnection::GetResponse()
{
Handle<HttpResponse> response=new HttpResponse();
response->ReadFromStream(this);
return response;
}

VOID HttpConnection::Send(Handle<HttpRequest> request)
{
request->WriteToStream(this);
pStream->Flush();
}

VOID HttpConnection::Send(Handle<HttpResponse> response)
{
response->WriteToStream(this);
pStream->Flush();
}

BOOL HttpConnection::SendFile(Handle<File> file, Handle<String> path)
{
if(!file)
	return false;
Handle<HttpRequest> request=new HttpRequest();
request->Content=file;
request->Method=HttpMethod::Post;
request->Parameters->Set("name", file->GetName());
request->Path=path;
request->Properties->Set("Content-Type", "application/octet-stream");
UINT64 pos=0;
UINT64 size=file->GetSize();
constexpr UINT chunk_size=1024*1024;
while(pos<size)
	{
	UINT64 copy=MIN(size-pos, chunk_size);
	UINT64 end=pos+copy;
	request->Properties->Set("Content-Length", new String("%u", copy));
	request->Properties->Set("Content-Range", new String("%u-%u/%u", pos, end, size));
	request->Properties->Set("Connection", end<size? "Keep-Alive": "Close");
	Send(request);
	auto response=GetResponse();
	if(response->Status!=HttpStatus::Ok)
		return false;
	pos+=copy;
	}
return true;
}


//==============
// Input-Stream
//==============

SIZE_T HttpConnection::Available()
{
return pStream->Available();
}

SIZE_T HttpConnection::Read(VOID* buf, SIZE_T size)
{
return pStream->Read(buf, size);
}


//===============
// Output-Stream
//===============

VOID HttpConnection::Flush()
{
pStream->Flush();
}

SIZE_T HttpConnection::Write(VOID const* buf, SIZE_T size)
{
return pStream->Write(buf, size);
}

}}