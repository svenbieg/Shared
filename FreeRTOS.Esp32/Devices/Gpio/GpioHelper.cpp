//================
// GpioHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <driver/gpio.h>
#include <esp_attr.h>
#include "GpioHelper.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//========
// Common
//========

BOOL DigitalRead(BYTE upin)
{
return gpio_get_level((gpio_num_t)upin);
}

VOID DigitalWrite(BYTE upin, BOOL b)
{
gpio_set_level((gpio_num_t)upin, b);
}

VOID SetPinMode(BYTE upin, PinMode mode)
{
gpio_config_t cfg;
ZeroMemory(&cfg, sizeof(gpio_config_t));
cfg.pin_bit_mask=1ULL<<upin;
cfg.mode=(mode==PinMode::Output? GPIO_MODE_OUTPUT: GPIO_MODE_INPUT);
cfg.pull_up_en=GPIO_PULLUP_DISABLE;
esp_err_t err=gpio_config(&cfg);
if(err!=ESP_OK)
	{
	DebugPrint("gpio_config failed (%u)\n", (UINT)err);
	}
}


//============
// Interrupts
//============

Mutex IRAM_ATTR cInterruptMutex;
UINT64 IRAM_ATTR uChangedPin=0;
UINT uInterruptPins=0;

VOID IRAM_ATTR InterruptProc(VOID* parg)
{
UINT pin=(UINT)parg;
UINT64 mask=1ULL<<pin;
ScopedLock lock(cInterruptMutex);
uChangedPin|=mask;
}

VOID AttachInterrupt(BYTE pin)
{
if(!uInterruptPins)
	gpio_install_isr_service(ESP_INTR_FLAG_EDGE|ESP_INTR_FLAG_IRAM);
uInterruptPins++;
gpio_config_t conf;
ZeroMemory(&conf, sizeof(gpio_config_t));
conf.intr_type=GPIO_INTR_ANYEDGE;
conf.pin_bit_mask=1ULL<<pin;
conf.mode=GPIO_MODE_INPUT;
gpio_config(&conf);
gpio_isr_handler_add((gpio_num_t)pin, InterruptProc, (VOID*)(UINT)pin);
}

VOID DetachInterrupt(BYTE pin)
{
gpio_config_t conf;
ZeroMemory(&conf, sizeof(gpio_config_t));
conf.pin_bit_mask=1ULL<<pin;
gpio_config(&conf);
if(--uInterruptPins==0)
	gpio_install_isr_service(ESP_INTR_FLAG_INTRDISABLED);
}

BOOL DetectInterrupt(BYTE pin)
{
BOOL changed=false;
UINT64 mask=1ULL<<pin;
	{
	ScopedLock lock(cInterruptMutex);
	changed=(uChangedPin&mask)>0;
	uChangedPin&=~mask;
	}
return changed;
}

}}
