//===============
// IpAddress.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "IpAddress.h"


//===========
// Namespace
//===========

namespace Network {


//==================
// Con-/Destructors
//==================

IpAddress::IpAddress(Handle<String> name, UINT ip):
TypedVariable(name, ip)
{}

IpAddress::IpAddress(Handle<String> name, BYTE a1, BYTE a2, BYTE a3, BYTE a4):
TypedVariable(name, 0)
{
tValue=From(a1, a2, a3, a4);
}


//========
// Access
//========

Handle<String> IpAddress::ToString()
{
UINT ip=Get();
return ToString(ip);
}

Handle<String> IpAddress::ToString(UINT ip)
{
BYTE* pip=(BYTE*)&ip;
UINT u1=pip[0];
UINT u2=pip[1];
UINT u3=pip[2];
UINT u4=pip[3];
return new String("%u.%u.%u.%u", u1, u2, u3, u4);
}


//==============
// Modification
//==============

BOOL IpAddress::FromString(Handle<String> value, BOOL notify)
{
if(!value)
	return false;
UINT u1=0;
UINT u2=0;
UINT u3=0;
UINT u4=0;
if(value->Scan("%u.%u.%u.%u", &u1, &u2, &u3, &u4)==4)
	{
	UINT ip=0;
	BYTE* pip=(BYTE*)&ip;
	pip[0]=(BYTE)u1;
	pip[1]=(BYTE)u2;
	pip[2]=(BYTE)u3;
	pip[3]=(BYTE)u4;
	TypedVariable::Set(ip, notify);
	return true;
	}
return false;
}


//========
// Common
//========

UINT IpAddress::From(BYTE a1, BYTE a2, BYTE a3, BYTE a4)
{
UINT ip=0;
BYTE* pip=(BYTE*)&ip;
pip[0]=a1;
pip[1]=a2;
pip[2]=a3;
pip[3]=a4;
return ip;
}

}
