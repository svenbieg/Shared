//===========
// OneWire.h
//===========

#pragma once


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//==========
// One-Wire
//==========

class OneWire: public Object
{
public:
	// Con-/Destructors
	OneWire(BYTE Pin);

	BYTE Read();
	VOID Read(VOID* Buffer, UINT Size);
	UINT Scan(UINT64* Ids, UINT Max);
	BOOL Select(UINT64 Id);
	VOID Write(BYTE Value);
	VOID Write(VOID const* Buffer, UINT Size);

private:
	// Common
	BYTE uPin;
};

}}