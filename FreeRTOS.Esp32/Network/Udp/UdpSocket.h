//=============
// UdpSocket.h
//=============

#pragma once


//===========
// Namespace
//===========

namespace Network {
	namespace Udp {


//============
// UDP-Socket
//============

class UdpSocket: public Object
{
public:
	// Con-/Destructors
	UdpSocket(INT Socket=-1);
	~UdpSocket();

	// Common
	static BOOL Broadcast(WORD Port, VOID const* Buffer, WORD Size);
	VOID Close();
	BOOL Listen(WORD Port);
	WORD Read(VOID* Buffer, WORD Size);

private:
	// Common
	INT iSocket;
};

}}