//===========
// Console.h
//===========

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"


//===========
// Namespace
//===========

namespace Console {


//=========
// Console
//=========

class Console: public Storage::Streams::RandomAccessStream
{
public:
	// Con-/Destructors
	Console();

	// Common
	static Handle<Console> Open();

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	static Handle<Console> hCurrent;
	HANDLE hInput;
	HANDLE hOutput;
	DWORD uCodePage;
};

}