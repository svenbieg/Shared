//==================
// AnalogHelper.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include <esp_adc/adc_oneshot.h>
#include "AnalogHelper.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//=========
// Globals
//=========

adc_oneshot_unit_handle_t hUnit=NULL;


//=================
// Analog Channels
//=================

const adc_channel_t pAnalogChannels[]={ ADC_CHANNEL_4, ADC_CHANNEL_5, ADC_CHANNEL_6, ADC_CHANNEL_7, ADC_CHANNEL_0, ADC_CHANNEL_9, ADC_CHANNEL_9, ADC_CHANNEL_3 };


//========
// Common
//========

FLOAT AnalogRead(BYTE pin)
{
if(!hUnit)
	{
	adc_oneshot_unit_init_cfg_t cfg;
	cfg.ulp_mode=ADC_ULP_MODE_RISCV;
	cfg.unit_id=ADC_UNIT_1;
	adc_oneshot_new_unit(&cfg, &hUnit);
	}
adc_channel_t ch=pAnalogChannels[pin-32];
adc_oneshot_chan_cfg_t ch_cfg;
ch_cfg.bitwidth=ADC_BITWIDTH_12;
ch_cfg.atten=ADC_ATTEN_DB_11;
adc_oneshot_config_channel(hUnit, ch, &ch_cfg);
INT input=0;
adc_oneshot_read(hUnit, ch, &input);
if(input==4095)
	return -1.f;
return (FLOAT)input*3.3f/4096.f;
}

FLOAT AnalogReadLinear(BYTE pin)
{
// https://www.instructables.com/Do-You-Know-About-ESP32-ADC-Adjustment/
FLOAT x=AnalogRead(pin);
FLOAT voltage=
	+2.161282383460e+02
	+3.944594843419e-01*x
	+5.395439724295e-04*x*x
	-3.968558178426e-06*x*x*x
	+1.047910519933e-08*x*x*x*x
	-1.479271312313e-11*x*x*x*x*x
	+1.220894795714e-14*x*x*x*x*x*x
	-6.136200785076e-18*x*x*x*x*x*x*x
	+1.910015248179e-21*x*x*x*x*x*x*x*x
	-3.566607830903e-25*x*x*x*x*x*x*x*x*x
	+5.000280815521e-30*x*x*x*x*x*x*x*x*x*x
	+3.434515045670e-32*x*x*x*x*x*x*x*x*x*x*x
	-1.407635444704e-35*x*x*x*x*x*x*x*x*x*x*x*x
	+9.871816383223e-40*x*x*x*x*x*x*x*x*x*x*x*x*x;
return voltage;
}

}}
