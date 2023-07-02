//===================
// ImpulseHelper.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include <driver/pulse_cnt.h>
#include <esp_attr.h>
#include "ImpulseHelper.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//=========
// Globals
//=========

#define PCNT_MAX 4

typedef struct
{
BYTE Pin;
pcnt_channel_handle_t Channel;
pcnt_unit_handle_t Unit;
}Pcnt;

Pcnt Pcnts[PCNT_MAX]={{ 0, NULL, NULL }};

Pcnt* GetPcnt(BYTE pin)
{
for(UINT u=0; u<PCNT_MAX; u++)
	{
	if(Pcnts[u].Pin==pin)
		return &Pcnts[u];
	}
return nullptr;
}


//========
// Common
//========

VOID ImpulseClear(BYTE pin)
{
auto pcnt=GetPcnt(pin);
if(!pcnt)
	return;
pcnt_unit_clear_count(pcnt->Unit);
}

VOID ImpulseClose(BYTE pin)
{
for(UINT u=0; u<PCNT_MAX; u++)
	{
	if(Pcnts[u].Pin==pin)
		{
		pcnt_del_channel(Pcnts[u].Channel);
		pcnt_del_unit(Pcnts[u].Unit);
		Pcnts[u].Unit=NULL;
		Pcnts[u].Channel=NULL;
		Pcnts[u].Pin=0;
		break;
		}
	}
}

UINT ImpulseCount(BYTE pin)
{
auto pcnt=GetPcnt(pin);
if(!pcnt)
	return 0;
INT count=0;
if(pcnt_unit_get_count(pcnt->Unit, &count)!=ESP_OK)
	return 0;
return count;
}

VOID ImpulseInit(BYTE pin)
{
auto pcnt=GetPcnt(0);
if(!pcnt)
	return;
pcnt_unit_config_t unit_cfg;
ZeroMemory(&unit_cfg, sizeof(pcnt_unit_config_t));
unit_cfg.high_limit=INT_MAX;
pcnt_unit_handle_t unit=nullptr;
if(pcnt_new_unit(&unit_cfg, &unit)!=ESP_OK)
	return;
pcnt_chan_config_t ch_cfg;
ZeroMemory(&ch_cfg, sizeof(pcnt_chan_config_t));
ch_cfg.edge_gpio_num=pin;
ch_cfg.level_gpio_num=-1;
pcnt_channel_handle_t channel=NULL;
if(pcnt_new_channel(unit, &ch_cfg, &channel)!=ESP_OK)
	{
	pcnt_del_unit(unit);
	return;
	}
pcnt_channel_set_edge_action(channel, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_HOLD);
pcnt->Unit=unit;
pcnt->Channel=channel;
pcnt->Pin=pin;
pcnt_unit_start(unit);
}

}}