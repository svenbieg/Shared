//===============
// PwmHelper.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <driver/ledc.h>
#include "Devices/Gpio/GpioHelper.h"
#include "PwmHelper.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//=========
// Globals
//=========

BYTE pLedcChannelPin[LEDC_CHANNEL_MAX]={ 0, 0, 0, 0, 0, 0, 0, 0 };
BYTE pLedcChannelTimer[LEDC_CHANNEL_MAX]={ 0, 0, 0, 0, 0, 0, 0, 0 };
BYTE pLedcPins[]={ 5, 17, 18, 19, 21, 22, 23, 25, 26 };
UINT pLedcTimerPeriod[LEDC_TIMER_MAX]={ 0, 0, 0, 0 };
BYTE uLedcChannelCount=0;
BYTE uLedcTimerCount=0;

BYTE LedcGetChannel(BYTE upin)
{
for(BYTE u=0; u<uLedcChannelCount; u++)
	{
	if(pLedcChannelPin[u]==upin)
		return u;
	}
return LEDC_CHANNEL_MAX;
}


//========
// Common
//========

VOID PwmInit(BYTE pin, UINT period)
{
BOOL valid=false;
for(BYTE u=0; u<ARRAYSIZE(pLedcPins); u++)
	{
	if(pLedcPins[u]==pin)
		{
		valid=true;
		break;
		}
	}
if(!valid)
	{
	DebugPrint("PwmInit - Invalid Pin %u\n", pin);
	return;
	}
if(uLedcChannelCount==LEDC_CHANNEL_MAX)
	{
	DebugPrint("PwmInit - Max channels\n");
	return;
	}
BYTE timer=LEDC_TIMER_MAX;
for(BYTE u=0; u<uLedcTimerCount; u++)
	{
	if(pLedcTimerPeriod[u]==period)
		{
		timer=u;
		break;
		}
	}
if(timer==LEDC_TIMER_MAX)
	{
	if(uLedcTimerCount==LEDC_TIMER_MAX)
		{
		DebugPrint("PwmInit - Max timers\n");
		return;
		}
	timer=uLedcTimerCount;
	ledc_timer_config_t tc;
	ZeroMemory(&tc, sizeof(ledc_timer_config_t));
	tc.duty_resolution=LEDC_TIMER_10_BIT;
	tc.clk_cfg=LEDC_AUTO_CLK;
	tc.freq_hz=1000000/period;
	tc.speed_mode=LEDC_LOW_SPEED_MODE;
	tc.timer_num=(ledc_timer_t)timer;
	if(ledc_timer_config(&tc)!=ESP_OK)
		{
		DebugPrint("ledc_timer_config() failed\n");
		return;
		}
	pLedcTimerPeriod[timer]=period;
	uLedcTimerCount++;
	}
BYTE channel=uLedcChannelCount;
ledc_channel_config_t cc;
ZeroMemory(&cc, sizeof(ledc_channel_config_t));
cc.channel=(ledc_channel_t)channel;
cc.gpio_num=pin;
cc.timer_sel=(ledc_timer_t)timer;
cc.speed_mode=LEDC_LOW_SPEED_MODE;
if(ledc_channel_config(&cc)!=ESP_OK)
	{
	DebugPrint("ledc_channel_config() failed\n");
	return;
	}
pLedcChannelPin[channel]=pin;
pLedcChannelTimer[channel]=timer;
uLedcChannelCount++;
}

VOID PwmSetDuty(BYTE pin, UINT duty_us)
{
BYTE channel=LedcGetChannel(pin);
if(channel==LEDC_CHANNEL_MAX)
	return;
BYTE timer=pLedcChannelTimer[channel];
UINT period=pLedcTimerPeriod[timer];
UINT duty=duty_us*1023/period;
/*if(duty==0||duty==1023)
	{
	ledc_stop(LEDC_LOW_SPEED_MODE, (ledc_channel_t)uchannel, 0);
	SetPinMode(upin, PinMode::Output);
	DigitalWrite(pin, duty==1023);
	DebugPrint("ledc_stop()\r\n");
	return;
	}*/
ledc_set_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)channel, duty);
ledc_update_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)channel);
DebugPrint("ledc_set_duty - Pin:%u Timer:%u Channel:%u Duty:%u\n", pin, timer, channel, duty);
}

}}
