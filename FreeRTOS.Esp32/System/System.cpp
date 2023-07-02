//============
// System.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include <esp_sleep.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include "Storage/Filesystem/Partition.h"
#include "System.h"

using namespace Physics;
using namespace Storage::Filesystem;


//===========
// Namespace
//===========

namespace System {


//========
// Common
//========

WakeupReason System::GetWakeupReason()
{
auto cause=esp_sleep_get_wakeup_cause();
switch(cause)
	{
	case ESP_SLEEP_WAKEUP_TIMER:
		return WakeupReason::Timer;
	case ESP_SLEEP_WAKEUP_TOUCHPAD:
		return WakeupReason::Touchpad;
	default:
		break;
	}
return WakeupReason::None;
}

VOID System::Reset()
{
auto db=Partition::Open();
db->Clear();
esp_restart();
}

VOID System::Restart()
{
esp_restart();
}

VOID System::Sleep(UINT ums)
{
esp_wifi_stop();
esp_deep_sleep(ums*1000);
}

VOID System::SleepTouchable(UINT ums)
{
esp_sleep_enable_touchpad_wakeup();
Sleep(ums);
}

Handle<TimePoint> System::Start=new TimePoint("SystemStart");

const FLOAT System::Voltage=3.3f;

}