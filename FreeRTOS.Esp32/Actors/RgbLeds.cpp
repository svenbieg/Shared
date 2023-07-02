//=============
// RgbLeds.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <driver/rmt_encoder.h>
#include <driver/rmt_tx.h>
#include "RgbLeds.h"

using namespace Graphics;


//===========
// Namespace
//===========

namespace Actors {


//==========
// Settings
//==========

constexpr UINT LED_FREQUENCY=10000000;

constexpr UINT T0H=LED_FREQUENCY*300/1000000000U; // 300us
constexpr UINT T0L=LED_FREQUENCY*900/1000000000U; // 900us
constexpr UINT T1H=T0L;
constexpr UINT T1L=T0H;


//==================
// Con-/Destructors
//==================

RgbLeds::RgbLeds(BYTE pin, UINT count, BYTE channel):
bChanged(true),
cColorBuffer(count*3),
pByteEncoder(nullptr),
pChannel(nullptr),
uLedCount(count),
uPin(pin)
{
if(!Initialize())
	return;
cColorBuffer.Zero();
Flush();
}

RgbLeds::~RgbLeds()
{
if(pChannel)
	{
	cColorBuffer.Zero();
	Flush();
	}
Close();
}


//========
// Common
//========

VOID RgbLeds::Flush()
{
if(!pChannel||!bChanged)
	return;
auto channel=(rmt_channel_handle_t)pChannel;
auto encoder=(rmt_encoder_handle_t)pByteEncoder;
BYTE* colors=cColorBuffer.Begin();
UINT size=cColorBuffer.GetSize();
rmt_transmit_config_t cfg;
ZeroMemory(&cfg, sizeof(rmt_transmit_config_t));
rmt_transmit(channel, encoder, colors, size, &cfg);
bChanged=false;
}

VOID RgbLeds::SetColor(UINT led, COLOR c, FLOAT brightness)
{
if(led>=uLedCount)
	return;
c.SetBrightness(brightness);
BYTE r=c.GetRed();
BYTE g=c.GetGreen();
BYTE b=c.GetBlue();
BYTE* pbuf=cColorBuffer.Begin();
pbuf+=led*3;
if(pbuf[0]!=r)
	{
	pbuf[0]=r;
	bChanged=true;
	}
if(pbuf[1]!=g)
	{
	pbuf[1]=g;
	bChanged=true;
	}
if(pbuf[2]!=b)
	{
	pbuf[2]=b;
	bChanged=true;
	}
}


//================
// Common Private
//================

VOID RgbLeds::Close()
{
if(pChannel!=nullptr)
	rmt_del_channel((rmt_channel_handle_t)pChannel);
if(pByteEncoder!=nullptr)
	rmt_del_encoder((rmt_encoder_handle_t)pByteEncoder);
}

BOOL RgbLeds::Initialize()
{
rmt_tx_channel_config_t channel_cfg;
ZeroMemory(&channel_cfg, sizeof(rmt_tx_channel_config_t));
channel_cfg.gpio_num=uPin;
channel_cfg.clk_src=RMT_CLK_SRC_DEFAULT;
channel_cfg.resolution_hz=LED_FREQUENCY;
channel_cfg.mem_block_symbols=64;
channel_cfg.trans_queue_depth=4;
rmt_channel_handle_t channel=nullptr;
if(rmt_new_tx_channel(&channel_cfg, &channel)!=ESP_OK)
	{
	DebugPrint("rmt_new_tx_channel() failed\n");
	Close();
	return false;
	}
pChannel=channel;
rmt_bytes_encoder_config_t byte_encoder_cfg;
ZeroMemory(&byte_encoder_cfg, sizeof(rmt_bytes_encoder_config_t));
byte_encoder_cfg.bit0.level0=1;
byte_encoder_cfg.bit0.duration0=T0H;
byte_encoder_cfg.bit0.duration1=T0L;
byte_encoder_cfg.bit1.level0=1;
byte_encoder_cfg.bit1.duration0=T1H;
byte_encoder_cfg.bit1.duration1=T1L;
byte_encoder_cfg.flags.msb_first=1;
rmt_encoder_handle_t byte_encoder=nullptr;
if(rmt_new_bytes_encoder(&byte_encoder_cfg, &byte_encoder)!=ESP_OK)
	{
	DebugPrint("rmt_new_bytes_encoder() failed\n");
	Close();
	return false;
	}
pByteEncoder=byte_encoder;
if(rmt_enable(channel)!=ESP_OK)
	{
	DebugPrint("rmt_enable() failed\n");
	Close();
	return false;
	}
return true;
}

}