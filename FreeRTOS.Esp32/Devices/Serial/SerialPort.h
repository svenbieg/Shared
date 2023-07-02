//==============
// SerialPort.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Serial {


//===========
// Baud-Rate
//===========

enum class BaudRate: UINT
{
Baud57600=57600,
Baud74880=74880,
Baud115200=115200
};


//=============
// Serial Port
//=============

class SerialPort: public Storage::Streams::RandomAccessStream
{
public:
	// Con-/Destructors
	SerialPort(UINT Id=0, BaudRate BaudRate=BaudRate::Baud115200);
	~SerialPort();

	// Common
	VOID ClearBuffer();
	static Handle<SerialPort> Open();

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size);

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	Mutex cMutex;
	static Handle<SerialPort> hDefault;
	UINT uId;
};

}}
