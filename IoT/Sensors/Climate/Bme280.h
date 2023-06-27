//==========
// Bme280.h
//==========

#pragma once


//=======
// Using
//=======

#include "Core/Timer.h"
#include "Physics/Humidity.h"
#include "Physics/Pressure.h"
#include "Sensors/Temperature/Thermometer.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Climate {


//======
// Mode
//======

enum class Bme280Mode: BYTE
{
Sleep=0,
Forced=1,
Normal=3
};


//=========
// Standby
//=========

enum class Bme280Standby: BYTE
{
MS0_5=0,
MS62_5=1,
MS125=2,
MS250=3,
MS500=4,
MS1000=5,
MS10=6,
MS20=7
};


//==============
// Oversampling
//==============

enum class Bme280Osr: BYTE
{
Off=0,
X1=1,
X2=2,
X4=3,
X8=4,
X16=5
};


//========
// Filter
//========

enum class Bme280Filter: BYTE
{
Off=0,
X2=1,
X4=2,
X8=3,
X16=4
};


//==========
// Settings
//==========

class Bme280Settings
{
public:
	// Con-/Destructors
	Bme280Settings();

	// Common
	Bme280Filter Filter;
	Bme280Osr HumidityOsr;
	BYTE I2cAddress;
	Bme280Mode Mode;
	Bme280Osr PressureOsr;
	Bme280Standby Standby;
	Bme280Osr TemperatureOsr;
};


//========
// BME280
//========

class Bme280: public Sensors::Temperature::Thermometer
{
public:
	// Using
	using Timer=Core::Timer;

	// Con-/Destructors
	Bme280(Handle<String> Id, Bme280Settings* Settings=nullptr);

	// Common
	Handle<Physics::Humidity> Humidity;
	BOOL IsPresent();
	Handle<Physics::Pressure> Pressure;
	VOID Sleep();
	VOID Update();

private:
	// Common
	FLOAT CalculateHumidity(UINT Raw, INT Fine);
	FLOAT CalculatePressure(UINT Raw, INT Fine);
	FLOAT CalculateTemperature(UINT Raw, INT& Fine);
	VOID OnTimerTriggered();
	UINT StandbyToMillis(Bme280Standby Standby);
	VOID WriteDeviceSettings();
	Bme280Settings cSettings;
	Handle<Timer> hTimer;
	BYTE pCalibration[33];
};

}}