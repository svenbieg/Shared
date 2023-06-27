//=============
// OneWire.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "OneWire.h"
#include "OneWireHelper.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==================
// Con-/Destructors
//==================

OneWire::OneWire(BYTE upin):
uPin(upin)
{}


//========
// Common
//========

BYTE OneWire::Read()
{
BYTE uvalue=0;
for(BYTE u=0; u<8; u++)
	{
	uvalue>>=1;
	if(OneWireReadBit(uPin))
		uvalue|=0x80;
	}
return uvalue;
}

VOID OneWire::Read(VOID* pbufv, UINT usize)
{
auto pbuf=(BYTE*)pbufv;
for(UINT u=0; u<usize; u++)
	pbuf[u]=Read();
}

UINT OneWire::Scan(UINT64* pids, UINT umax)
{
UINT uidcount=0;
BYTE pbuf[8];
ZeroMemory(pbuf, 8);
BYTE uoldlastzero=0;
for(UINT uid=0; uid<umax; uid++)
	{
	if(!OneWireReset(uPin))
		return 0;
	Write(0xF0);
	BYTE uidbit=1;
	BYTE uidbyte=0;
	BYTE uidmask=1;
	BYTE ulastzero=0;
	do
		{
		BOOL bval=OneWireReadBit(uPin);
		BOOL bcmp=OneWireReadBit(uPin);
		if(bval&&bcmp)
			return 0;
		if(bval==bcmp)
			{
			if(uidbit<uoldlastzero)
				{
				bval=(pbuf[uidbyte]&uidmask)>0;
				}
			else
				{
				bval=(uidbit==uoldlastzero);
				}
			if(!bval)
				{
				ulastzero=uidbit;
				}
			}
		if(bval)
			{
			pbuf[uidbyte]|=uidmask;
			}
		else
			{
			pbuf[uidbyte]&=~uidmask;
			}
		OneWireWriteBit(uPin, bval);
		uidbit++;
		uidmask<<=1;
		if(uidmask==0)
			{
			uidbyte++;
			uidmask=1;
			}
		}
	while(uidbyte<8);
	if(uidbit<65)
		break;
	uoldlastzero=ulastzero;
	CopyMemory(&pids[uidcount], pbuf, 8);
	uidcount++;
	if(ulastzero==0)
		break;
	}
return uidcount;
}

BOOL OneWire::Select(UINT64 uid)
{
if(!OneWireReset(uPin))
	return false;
Write(0x55);
auto pid=(BYTE*)&uid;
for(BYTE u=0; u<8; u++)
	Write(pid[u]);
return true;
}

VOID OneWire::Write(BYTE uvalue)
{
for(BYTE u=0; u<8; u++)
	{
	OneWireWriteBit(uPin, uvalue&0x01);
	uvalue>>=1;
	}
}

VOID OneWire::Write(VOID const* pbufv, UINT usize)
{
auto pbuf=(BYTE const*)pbufv;
for(UINT u=0; u<usize; u++)
	Write(pbuf[u]);
}

}}