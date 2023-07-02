//============
// TaskLock.h
//============

#pragma once


//===========
// Task-Lock
//===========

class TaskLock
{
public:
	// Con-/Destructors
	TaskLock();
	~TaskLock();

	// Common
	VOID Release();

private:
	// Common
	UINT64 uMutex;
};
