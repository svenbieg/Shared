//==============
// KTY-81-210.h
//==============
//
// Connection:
// Vss - Sensor - AI - 4.7k+0.1uF - 0V
//

#pragma once


//=======
// Using
//=======

#include "Devices/Gpio/AnalogPin.h"
#include "Thermometer.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//============
// KTY-81-210
//============

class Kty_81_210: public Thermometer
{
private:
	// Using
	using AnalogPin=Devices::Gpio::AnalogPin;

public:
	// Con-/Destructors
	Kty_81_210(Handle<String> Id, Handle<AnalogPin> AnalogPin, FLOAT Voltage=3.3f, FLOAT Resistor=4700.f);

private:
	// Common
	VOID OnValueChanged();
	FLOAT fResistor;
	FLOAT fVoltage;
	Handle<AnalogPin> hPin;
	UINT uErrorTime;
};

}}
