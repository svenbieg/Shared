//===========
// GpioPin.h
//===========

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==========
// GPIO-Pin
//==========

class GpioPin: public Object
{
public:
	// Using
	using PinMap=Collections::Map<Handle<String>, GpioPin*>;

	// Common
	Handle<String> GetId()const { return hId; }
	BYTE GetPin()const { return uPin; }
	static Handle<PinMap> Pins;

protected:
	// Con-/Destructors
	GpioPin(Handle<String> Id, BYTE Pin);
	~GpioPin();

	// Common
	Handle<String> hId;
	BYTE uPin;
};

}}