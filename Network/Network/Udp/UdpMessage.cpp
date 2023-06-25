//================
// UdpMessage.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "UdpMessage.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Udp {


//==================
// Con-/Destructors
//==================

UdpMessage::UdpMessage(VOID const* buf, WORD size):
pBuffer(nullptr),
uSize(0)
{
if(size==0)
	return;
pBuffer=new BYTE[size];
CopyMemory(pBuffer, buf, size);
uSize=size;
}

UdpMessage::~UdpMessage()
{
if(pBuffer)
	delete pBuffer;
}

}}
