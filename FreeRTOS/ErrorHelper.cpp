//=================
// ErrorHelper.cpp
//=================

#include "pch.h"


#ifdef _DEBUG

//=======
// Using
//=======

#include "Devices/Serial/SerialPort.h"
#include "Storage/Streams/StringWriter.h"
#include "ErrorHelper.h"

using namespace Devices::Serial;
using namespace Storage::Streams;


//========
// Common
//========


VOID DebugPrint(LPCSTR text)
{
auto serial=SerialPort::Open();
StringWriter writer(serial);
writer.Print(text);
}

#endif
