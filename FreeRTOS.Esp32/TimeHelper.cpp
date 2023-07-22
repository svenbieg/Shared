//================
// TimeHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <rom/ets_sys.h>
#include <esp_timer.h>


//========
// Common
//========

UINT GetTickCount()
{
return (UINT)(esp_timer_get_time()/1000);
}

UINT64 GetTickCount64()
{
return esp_timer_get_time()/1000;
}

UINT64 GetTickCountUs()
{
return esp_timer_get_time();
}

VOID Sleep(UINT millis)
{
vTaskDelay(millis/portTICK_PERIOD_MS);
}

VOID SleepMicroseconds(UINT us)
{
ets_delay_us(us);
}
