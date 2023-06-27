//=============
// GpioPin.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "GpioPin.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//========
// Common
//========

Handle<GpioPin::PinMap> GpioPin::Pins;


//============================
// Con-/Destructors Protected
//============================

GpioPin::GpioPin(Handle<String> id, BYTE pin):
hId(id),
uPin(pin)
{
if(!Pins)
	Pins=new PinMap();
Pins->Add(hId, this);
}

GpioPin::~GpioPin()
{
Pins->Remove(hId);
if(Pins->GetCount()==0)
	Pins=nullptr;
}

}}