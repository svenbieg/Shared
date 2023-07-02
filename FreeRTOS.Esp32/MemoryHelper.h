//================
// MemoryHelper.h
//================

#pragma once


//=======
// Using
//=======

#include <string.h>
#include "TypeHelper.h"


//==========
// Settings
//==========

#define MAX_PATH 256
#define PAGE_SIZE 4096


//========
// Common
//========

inline INT CompareMemory(VOID const* Buffer1, VOID const* Buffer2, SIZE_T Size)
{
return memcmp(Buffer1, Buffer2, Size);
}

inline VOID CopyMemory(VOID* Destination, VOID const* Source, SIZE_T Size)
{
memcpy(Destination, Source, Size);
}

inline VOID FillMemory(VOID* Destination, SIZE_T Size, INT Value)
{
memset(Destination, Value, Size);
}

inline VOID MoveMemory(VOID* Destination, VOID const* Source, SIZE_T Size)
{
memmove(Destination, Source, Size);
}

inline VOID ZeroMemory(VOID* Buffer, SIZE_T Size)
{
memset(Buffer, 0, Size);
}


//============
// Allocation
//============

VOID* Alloc(SIZE_T Size);
VOID* AlignedAlloc(SIZE_T Size, SIZE_T Align);
VOID AlignedFree(VOID* Buffer);
VOID* DeviceAlloc(SIZE_T Size);
VOID DeviceFree(VOID* Buffer);
VOID Free(VOID* Buffer);


//==========
// Pointers
//==========

BOOL IsPointerStatic(VOID const* Pointer);
