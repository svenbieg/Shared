//===============
// FlashDevice.h
//===============

#pragma once


//=======
// Using
//=======

#include <esp_flash.h>
#include "Storage/Volume.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Storage {


//==============
// Flash-Device
//==============

class FlashDevice: public ::Storage::Volume
{
public:
	// Common
	VOID Erase(UINT64 Offset, UINT Size);
	UINT GetBlockSize()override;
	FILE_SIZE GetSize()override { return uSize; }
	static Handle<FlashDevice> Open();
	SIZE_T Read(FILE_SIZE Offset, VOID* Buffer, SIZE_T Size)override;
	BOOL SetSize(FILE_SIZE Size)override;
	SIZE_T Write(FILE_SIZE Offset, VOID const* Buffer, SIZE_T Size)override;

private:
	// Con-/Destructors
	FlashDevice();

	// Common
	UINT DiskOffset(UINT* Offset);
	static Handle<FlashDevice> hCurrent;
	UINT uOffset;
	UINT uSize;
};

}}
