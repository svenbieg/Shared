//=========
// Email.h
//=========

#pragma once


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
	// Con-/Destructors
	Email();

	// Common
	Event<Email> Aborted;
	Handle<String> From;
	VOID Send(Handle<String> Server, Handle<String> User, Handle<String> Password);
	Event<Email> Sent;
	Handle<String> Subject;
	Handle<String> Text;
	Handle<String> To;

private:
	// Common
	static VOID SendProc(VOID* Param);
	VOID DoAbort(VOID* SslContext, VOID* NetContext);
	VOID DoSend();
	VOID OnAborted();
	VOID OnSent();
	SIZE_T ReceiveData(VOID* NetContext, LPSTR Buffer, SIZE_T Size, INT* Status);
	SIZE_T ReceiveDataSsl(VOID* SslContext, LPSTR Buffer, SIZE_T Size, INT* Status);
	SIZE_T SendAndReceive(VOID* NetContext, LPSTR Buffer, SIZE_T Size, SIZE_T BufferSize, INT* Status);
	SIZE_T SendAndReceiveSsl(VOID* SslContext, LPSTR Buffer, SIZE_T Size, SIZE_T BufferSize, INT* Status);
	SIZE_T SendData(VOID* NetContext, LPCSTR Buffer, SIZE_T Size);
	SIZE_T SendDataSsl(VOID* SslContext, LPCSTR Buffer, SIZE_T Size);
	Handle<Email> hCallback;
	Handle<String> hPassword;
	Handle<String> hServer;
	Handle<String> hUser;
};

}}