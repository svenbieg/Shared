//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_ota_ops.h>
#include <time.h>
#include "Devices/Serial/SerialPort.h"
#include "Devices/Clock.h"
#include "Console/Application.h"
#include "System/System.h"

using namespace Console;
using namespace Devices;
using namespace Devices::Serial;

extern VOID Initialize();


//=============
// Entry-Point
//=============

extern "C" VOID app_main()
{
DebugPrint("app_main()\n");
setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", true);
tzset();
auto clock=Clock::Get();
System::System::Start=clock->Now();
Initialize();
auto app=Application::Current;
auto ota_desc=esp_ota_get_app_description();
app->Version=ota_desc->version;
app->Run();
}
