//===============
// TaskClass.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "Core/Application.h"
#include "TaskClass.h"

using namespace Core;


//==================
// Con-/Destructors
//==================

Task::Task(std::function<VOID()> proc):
Cancelled(false),
cProcedure(proc),
pTask(nullptr)
{
xTaskCreate(TaskProc, nullptr, PAGE_SIZE, this, tskIDLE_PRIORITY+1, (TaskHandle_t*)&pTask);
}

Task::~Task()
{
Cancel();
}


//========
// Common
//========

VOID Task::Cancel()
{
ScopedLock lock(cMutex);
if(!pTask)
	return;
Cancelled=true;
lock.Unlock();
Wait();
}

Task* Task::GetTask(UINT id)
{
Task* task=nullptr;
cTasks.try_get(id, &task);
return task;
}

VOID Task::Wait()
{
ScopedLock lock(cMutex);
if(!pTask)
	return;
auto task=GetCurrentTask();
if(!task)
	Application::Current->HandleDispatched();
cFinished.Wait(lock);
}


//================
// Common Private
//================

VOID Task::DoTask()
{
try
	{
	cProcedure();
	}
catch(std::exception&)
	{
	}
UINT id=(UINT)pTask;
cTasks.remove(id);
ScopedLock lock(cMutex);
cProcedure=nullptr;
vTaskDelete((TaskHandle_t)pTask);
pTask=nullptr;
cFinished.Broadcast();
}

VOID Task::TaskProc(VOID* param)
{
auto task=(Task*)param;
UINT id=task->GetId();
cTasks.add(id, task);
task->DoTask();
}

Clusters::shared_map<UINT, Task*> Task::cTasks;
