//=============
// TcpSocket.h
//=============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//============
// TCP-Socket
//============

class TcpSocket: public Storage::Streams::RandomAccessStream
{
public:
	// Con-/Destructors
	TcpSocket(INT Socket=-1);
	~TcpSocket();

	// Common
	Handle<TcpSocket> Accept();
	virtual VOID Close();
	virtual BOOL Connect(Handle<String> HostName, WORD Port);
	INT GetSocket()const { return iSocket; }
	VOID Listen(WORD Port);

	// Input-Stream
	SIZE_T Available()override;
	virtual SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	virtual SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

protected:
	// Common
	INT iSocket;
};

}}