//=========
// Email.h
//=========

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/InputStream.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Smtp {


//========
// E-Mail
//========

class Email: public Object
{
public:
	// Using
	using InputStream=Storage::Streams::InputStream;

	// Con-/Destructors
	Email();

	// Common
	Handle<String> From;
	VOID Send(Handle<String> Server, Handle<String> User, Handle<String> Password);
	Handle<String> Subject;
	Handle<String> Text;
	Handle<String> To;

private:
	// Common
	VOID DoSend(Handle<String> Server, Handle<String> User, Handle<String> Password);
	INT ReadStatus(InputStream* Stream, LPSTR Buffer, UINT BufferSize);
};

}}