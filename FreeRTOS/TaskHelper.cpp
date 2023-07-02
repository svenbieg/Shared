//================
// TaskHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "TaskHelper.h"


//========
// Common
//========

Task* GetCurrentTask()
{
UINT id=(UINT)xTaskGetCurrentTaskHandle();
return Task::GetTask(id);
}
