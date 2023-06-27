//=============
// DS18B20.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "DS18B20.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//==================
// Con-/Destructors
//==================

DS18B20::DS18B20(Handle<String> hid, Handle<OneWire> hbus, UINT64 uid, DS18B20Resolution res):
Thermometer(hid),
hOneWire(hbus),
uId(uid),
uResolution(res)
{
WriteResolution();
BeginConversion();
hTimer=new Timer();
hTimer->Triggered.Add(this, &DS18B20::OnTimerTriggered);
hTimer->StartPeriodic(1000);
}


//========
// Common
//========

VOID DS18B20::SetResolution(DS18B20Resolution res)
{
uResolution=res;
WriteResolution();
}


//================
// Common Private
//================

VOID DS18B20::BeginConversion()
{
if(!hOneWire->Select(uId))
	{
	Temperature=-300.f;
	return;
	}
hOneWire->Write(0x44);
}

VOID DS18B20::ReadResolution()
{
if(!hOneWire->Select(uId))
	{
	Temperature=-300.f;
	return;
	}
hOneWire->Write(0xBE);
BYTE pbuf[5];
hOneWire->Read(pbuf, 5);
uResolution=(DS18B20Resolution)((pbuf[4]>>5)&0x03);
}

VOID DS18B20::ReadTemperature()
{
if(!hOneWire->Select(uId))
	{
	Temperature=-300.f;
	return;
	}
hOneWire->Write(0xBE);
BYTE pbuf[2];
hOneWire->Read(pbuf, 2);
BYTE pmask[4]={ 0xFF, 0xFE, 0xFC, 0xF8 };
pbuf[0]&=pmask[(BYTE)uResolution];
WORD utemp=((WORD)pbuf[1]<<8)|pbuf[0];
Temperature=(FLOAT)utemp/16.f;
}

VOID DS18B20::WriteResolution()
{
if(!hOneWire->Select(uId))
	return;
hOneWire->Write(0x4E);
BYTE pbuf[3]={ 0, 0, 0 };
pbuf[2]=((BYTE)uResolution<<5)|0x1F;
hOneWire->Write(pbuf, 3);
}

VOID DS18B20::OnTimerTriggered()
{
ReadTemperature();
BeginConversion();
}

}}
