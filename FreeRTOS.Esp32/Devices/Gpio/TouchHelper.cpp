//=================
// TouchHelper.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <driver/touch_pad.h>
#include "TouchHelper.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//======
// Pins
//======

typedef struct
{
BYTE Pin;
touch_pad_t TouchPad;
}TouchPadPin;

TouchPadPin TouchPadPins[]=
	{
	{ 2, TOUCH_PAD_NUM2 },
	{ 4, TOUCH_PAD_NUM0 },
	{ 12, TOUCH_PAD_NUM5 },
	{ 13, TOUCH_PAD_NUM4 },
	{ 14, TOUCH_PAD_NUM6 },
	{ 15, TOUCH_PAD_NUM3 },
	{ 27, TOUCH_PAD_NUM7 },
	{ 32, TOUCH_PAD_NUM9 },
	{ 33, TOUCH_PAD_NUM8 }
	};

touch_pad_t GetTouchPad(BYTE pin)
{
for(UINT u=0; u<ARRAYSIZE(TouchPadPins); u++)
	{
	if(TouchPadPins[u].Pin==pin)
		return TouchPadPins[u].TouchPad;
	}
return TOUCH_PAD_MAX;
}


//=========
// Globals
//=========

UINT TouchPadCount=0;


//========
// Common
//========

VOID TouchClose(BYTE pin)
{
TouchPadCount--;
if(TouchPadCount==0)
	touch_pad_deinit();
}

BOOL TouchInit(BYTE pin)
{
touch_pad_t touch_pad=GetTouchPad(pin);
if(touch_pad==TOUCH_PAD_MAX)
	{
	DebugPrint("Invalid Touch Pin %u\n", pin);
	return false;
	}
if(TouchPadCount++==0)
	{
	if(touch_pad_init()!=ESP_OK)
		{
		DebugPrint("touch_pad_init() failed\n");
		return false;
		}
	touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
	touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
	}
touch_pad_config(touch_pad, 0);
return true;
}

WORD TouchRead(BYTE pin)
{
touch_pad_t touch_pad=GetTouchPad(pin);
if(touch_pad==TOUCH_PAD_MAX)
	return 0;
WORD value=0;
touch_pad_read(touch_pad, &value);
return value;
}

VOID TouchTreshold(BYTE pin, WORD treshold)
{
touch_pad_t touch_pad=GetTouchPad(pin);
if(touch_pad==TOUCH_PAD_MAX)
	return;
touch_pad_config(touch_pad, treshold);
}

}}