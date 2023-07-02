//=============
// TaskClass.h
//=============

#pragma once


//=======
// Using
//=======

#include "Clusters/shared_map.hpp"


//======
// Task
//======

class Task: public Object
{
public:
	// Con-/Destructors
	Task(std::function<VOID()> Procedure);
	~Task();

	// Common
	VOID Cancel();
	volatile BOOL Cancelled;
	inline UINT GetId() { return (UINT)pTask; }
	static Task* GetTask(UINT Id);
	VOID Wait();

private:
	// Common
	VOID DoDestroy();
	VOID DoTask();
	static VOID TaskProc(VOID* Param);
	Signal cFinished;
	Mutex cMutex;
	std::function<VOID()> cProcedure;
	static Clusters::shared_map<UINT, Task*> cTasks;
	VOID* pTask;
};
