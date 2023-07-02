//=================
// MemoryClass.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <esp_heap_caps.h>
#include "MemoryClass.h"


//===========
// Namespace
//===========

namespace Devices {


//==================
// Con-/Destructors
//==================

Memory::Memory()
{
hCurrent=this;
multi_heap_info_t info;
heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
Available=new FileSize("MemoryAvailable", info.total_free_bytes);
Available->Reading.Add(this, &Memory::OnAvailableReading);
Total=new FileSize("MemoryTotal", info.total_free_bytes+info.total_allocated_bytes);
}


//========
// Common
//========

Handle<Memory> Memory::Get()
{
if(!hCurrent)
	new Memory();
return hCurrent;
}


//================
// Common Private
//================

VOID Memory::OnAvailableReading(FILE_SIZE& available)
{
multi_heap_info_t info;
heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
available=info.total_free_bytes;
}

Handle<Memory> Memory::hCurrent;

}
