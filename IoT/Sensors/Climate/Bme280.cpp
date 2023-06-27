//============
// Bme280.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Devices/I2C/I2CBus.h"
#include "Bme280.h"

using namespace Devices::I2C;


//===========
// Namespace
//===========

namespace Sensors {
	namespace Climate {


//==========
// Register
//==========

enum class Bme280Register: BYTE
{
TempPressCalibration=0x88,
Id=0xD0,
Reset=0xE0,
HumidityCalibration=0xE1,
HumidityControl=0xF2,
Status=0xF3,
PowerControl=0xF4,
Config=0xF5,
Data=0xF7
};

VOID ReadRegister(BYTE addr, Bme280Register reg, VOID* buf, UINT size)
{
auto i2c=I2CBus::Open();
i2c->BeginWrite(addr);
i2c->Write((BYTE)reg);
i2c->EndTransmission();
i2c->BeginRead(addr);
i2c->Read(buf, size);
i2c->EndTransmission();
}

VOID WriteRegister(BYTE addr, Bme280Register reg, VOID const* buf, UINT size)
{
auto i2c=I2CBus::Open();
i2c->BeginWrite(addr);
i2c->Write((BYTE)reg);
i2c->Write(buf, size);
i2c->EndTransmission();
}


//==========
// Settings
//==========

Bme280Settings::Bme280Settings():
Filter(Bme280Filter::Off),
HumidityOsr(Bme280Osr::X1),
I2cAddress(0x76),
Mode(Bme280Mode::Normal),
PressureOsr(Bme280Osr::X1),
Standby(Bme280Standby::MS1000),
TemperatureOsr(Bme280Osr::X1)
{}


//==================
// Con-/Destructors
//==================

Bme280::Bme280(Handle<String> hid, Bme280Settings* psettings):
Thermometer(hid+".Temperature")
{
Humidity=new Physics::Humidity(hid+".Humidity", -1);
Pressure=new Physics::Pressure(hid+".Pressure", -1);
BYTE id=0;
ReadRegister(cSettings.I2cAddress, Bme280Register::Id, &id, 1);
if(id!=0x60)
	{
	cSettings.I2cAddress=0;
	return;
	}
BYTE buf[4];
ReadRegister(cSettings.I2cAddress, Bme280Register::HumidityControl, buf, 4);
ReadRegister(cSettings.I2cAddress, Bme280Register::TempPressCalibration, pCalibration, 26);
ReadRegister(cSettings.I2cAddress, Bme280Register::HumidityCalibration, &pCalibration[26], 7);
if(psettings)
	CopyMemory(&cSettings, psettings, sizeof(Bme280Settings));
WriteDeviceSettings();
Update();
if(cSettings.Mode==Bme280Mode::Normal)
	{
	hTimer=new Timer();
	hTimer->Triggered.Add(this, &Bme280::OnTimerTriggered);
	UINT time=StandbyToMillis(cSettings.Standby);
	hTimer->StartPeriodic(time);
	}
}


//========
// Common
//========

BOOL Bme280::IsPresent()
{
return cSettings.I2cAddress>0;
}

VOID Bme280::Sleep()
{
if(cSettings.I2cAddress==0)
	return;
cSettings.Mode=Bme280Mode::Sleep;
WriteDeviceSettings();
}

VOID Bme280::Update()
{
if(cSettings.I2cAddress==0)
	return;
if(cSettings.Mode==Bme280Mode::Forced)
	WriteDeviceSettings();
BYTE data[8];
ReadRegister(cSettings.I2cAddress, Bme280Register::Data, data, 8);
UINT rawt=((UINT)data[3]<<12)|((UINT)data[4]<<4)|(data[5]>>4);
UINT rawp=((UINT)data[0]<<12)|((UINT)data[1]<<4)|(data[2]>>4);
UINT rawh=((UINT)data[6]<<8)|data[7];
INT fine=0;
FLOAT temp=CalculateTemperature(rawt, fine);
FLOAT hum=CalculateHumidity(rawh, fine);
FLOAT press=CalculatePressure(rawp, fine);
Humidity->Set(hum);
Pressure->Set(press);
Temperature->Set(temp);
}


//================
// Common Private
//================

FLOAT Bme280::CalculateHumidity(UINT raw, INT fine)
{
BYTE h1=pCalibration[25];
SHORT h2=((WORD)pCalibration[27]<<8)|pCalibration[26];
BYTE h3=pCalibration[28];
SHORT h4=((WORD)pCalibration[29]<<4)|(pCalibration[30]&0x0F);
SHORT h5=((WORD)pCalibration[31]<<4)|((pCalibration[30]>>4)&0x0F);
BYTE h6=pCalibration[32];
DOUBLE var1=((DOUBLE)fine)-76800.0;
DOUBLE var2=(((DOUBLE)h4)*64.0+(((DOUBLE)h5)/16384.0)*var1);
DOUBLE var3=raw-var2;
DOUBLE var4=((DOUBLE)h2)/65536.0;
DOUBLE var5=(1.0+(((DOUBLE)h3)/67108864.0)*var1);
DOUBLE var6=1.0+(((DOUBLE)h6)/67108864.0)*var1*var5;
var6=var3*var4*(var5*var6);
DOUBLE h=var6*(1.0-((DOUBLE)h1)*var6/524288.0);
h=MAX(h, 0);
h=MIN(h, 100);
return (FLOAT)h;
}

FLOAT Bme280::CalculatePressure(UINT raw, INT fine)
{
WORD p1=((WORD)pCalibration[7]<<8)|pCalibration[6];
SHORT p2=((WORD)pCalibration[9]<<8)|pCalibration[8];
SHORT p3=((WORD)pCalibration[11]<<8)|pCalibration[10];
SHORT p4=((WORD)pCalibration[13]<<8)|pCalibration[12];
SHORT p5=((WORD)pCalibration[15]<<8)|pCalibration[14];
SHORT p6=((WORD)pCalibration[17]<<8)|pCalibration[16];
SHORT p7=((WORD)pCalibration[19]<<8)|pCalibration[18];
SHORT p8=((WORD)pCalibration[21]<<8)|pCalibration[20];
SHORT p9=((WORD)pCalibration[23]<<8)|pCalibration[22];
DOUBLE var1=((DOUBLE)fine/2.0)-64000.0;
DOUBLE var2=var1*var1*((DOUBLE)p6)/32768.0;
var2=var2+var1*((DOUBLE)p5)*2.0;
var2=(var2/4.0)+(((DOUBLE)p4)*65536.0);
DOUBLE var3=((DOUBLE)p3)*var1*var1/524288.0;
var1=(var3+((DOUBLE)p2)*var1)/524288.0;
var1=(1.0+var1/32768.0)*((DOUBLE)p1);
DOUBLE p=300.0;
if(var1>0)
	{
	p=1048576.0-(DOUBLE)raw;
	p=(p-(var2/4096.0))*6250.0/var1;
	var1=((DOUBLE)p9)*p*p/2147483648.0;
	var2=p*((DOUBLE)p8)/32768.0;
	p=p+(var1+var2+((DOUBLE)p7))/16.0;
	p/=100.0;
	p=MAX(p, 300.0);
	p=MIN(p, 1100.0);
	}
return (FLOAT)p;
}

FLOAT Bme280::CalculateTemperature(UINT raw, INT& fine)
{
WORD t1=((WORD)pCalibration[1]<<8)|pCalibration[0];
SHORT t2=((WORD)pCalibration[3]<<8)|pCalibration[2];
SHORT t3=((WORD)pCalibration[5]<<8)|pCalibration[4];
DOUBLE var1=((DOUBLE)raw)/16384.0-((DOUBLE)t1)/1024.0;
var1=var1*((DOUBLE)t2);
DOUBLE var2=((DOUBLE)raw)/131072.0-((DOUBLE)t1)/8192.0;
var2=(var2*var2)*((DOUBLE)t3);
fine=(INT)(var1+var2);
DOUBLE t=(var1+var2)/5120.0;
if(t<-40.0)t=-300.0;
if(t>85.0)t=-300.0;
return (FLOAT)t;
}

VOID Bme280::OnTimerTriggered()
{
Update();
}

UINT Bme280::StandbyToMillis(Bme280Standby standby)
{
switch(standby)
	{
	case Bme280Standby::MS0_5:
		return 1;
	case Bme280Standby::MS10:
		return 10;
	case Bme280Standby::MS20:
		return 20;
	case Bme280Standby::MS62_5:
		return 62;
	case Bme280Standby::MS125:
		return 125;
	case Bme280Standby::MS250:
		return 250;
	case Bme280Standby::MS500:
		return 500;
	case Bme280Standby::MS1000:
		return 1000;
	}
return 0;
}

VOID Bme280::WriteDeviceSettings()
{
BYTE udata=(BYTE)cSettings.HumidityOsr;
WriteRegister(cSettings.I2cAddress, Bme280Register::HumidityControl, &udata, 1);
BYTE standby=(BYTE)cSettings.Standby;
BYTE filter=(BYTE)cSettings.Filter;
udata=(standby<<5)|(filter<<2);
WriteRegister(cSettings.I2cAddress, Bme280Register::Config, &udata, 1);
BYTE osrt=(BYTE)cSettings.TemperatureOsr;
BYTE osrp=(BYTE)cSettings.PressureOsr;
BYTE mode=(BYTE)cSettings.Mode;
udata=(osrt<<5)|(osrp<<2)|mode;
WriteRegister(cSettings.I2cAddress, Bme280Register::PowerControl, &udata, 1);
}

}}