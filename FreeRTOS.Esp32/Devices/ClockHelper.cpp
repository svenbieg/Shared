//=================
// ClockHelper.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <esp_ota_ops.h>
#include <esp_sntp.h>
#include <time.h>
#include "ClockHelper.h"

using namespace Physics;


//===========
// Namespace
//===========

namespace Devices {


//==========
// Callback
//==========

BOOL bClockSet=false;

VOID ClockCallback(timeval* pt)
{
if(sntp_get_sync_status()!=SNTP_SYNC_STATUS_COMPLETED)
	return;
esp_ota_mark_app_valid_cancel_rollback();
bClockSet=true;
}


//========
// Common
//========

BOOL ClockGetTime(TIMEPOINT& tp, UINT delta)
{
ZeroMemory(&tp, sizeof(TIMEPOINT));
if(!ClockIsSet())
	return false;
time_t t_now;
time(&t_now);
t_now-=delta;
tm tm_now;
localtime_r(&t_now, &tm_now);
if(tm_now.tm_year+1900<2000)
	return false;
tp.Second=tm_now.tm_sec;
tp.Minute=tm_now.tm_min;
tp.Hour=tm_now.tm_hour;
tp.DayOfWeek=tm_now.tm_wday;
tp.DayOfMonth=tm_now.tm_mday;
tp.Month=tm_now.tm_mon;
tp.Year=tm_now.tm_year;
return true;
}

BOOL ClockIsSet()
{
return bClockSet;
}

VOID ClockStartSync()
{
ClockStopSync();
esp_sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
esp_sntp_setservername(0, "pool.ntp.org");
sntp_set_time_sync_notification_cb(ClockCallback);
esp_sntp_init();
}

VOID ClockStopSync()
{
if(esp_sntp_enabled())
	esp_sntp_stop();
}

}