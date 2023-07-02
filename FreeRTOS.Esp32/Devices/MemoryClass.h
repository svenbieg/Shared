//===============
// MemoryClass.h
//===============

#pragma once


//=======
// Using
//=======

#include "Storage/FileSize.h"


//===========
// Namespace
//===========

namespace Devices {


//========
// Memory
//========

class Memory: public Object
{
public:
	// Using
	using FileSize=Storage::FileSize;

	// Con-/Destructors
	Memory();

	// Common
	Handle<FileSize> Available;
	static Handle<Memory> Get();
	Handle<FileSize> Total;

private:
	// Common
	VOID OnAvailableReading(FILE_SIZE& Available);
	static Handle<Memory> hCurrent;
};

}
