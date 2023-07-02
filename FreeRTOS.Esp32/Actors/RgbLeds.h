//===========
// RgbLeds.h
//===========

#pragma once


//=======
// Using
//=======

#include "Graphics/Color.h"
#include "Storage/Buffer.h"


//===========
// Namespace
//===========

namespace Actors {


//==========
// Rgb-Leds
//==========

class RgbLeds: public Object
{
public:
	// Using
	using Buffer=Storage::Buffer;
	using COLOR=Graphics::COLOR;

	// Con-/Destructors
	RgbLeds(BYTE Pin, UINT LedCount, BYTE RmtChannel=0);
	~RgbLeds();

	// Common
	VOID Flush();
	BYTE GetPin()const { return uPin; }
	VOID SetColor(UINT Led, COLOR Color, FLOAT Brightness=1.f);

private:
	// Common
	VOID Close();
	BOOL Initialize();
	BOOL bChanged;
	Buffer cColorBuffer;
	VOID* pByteEncoder;
	VOID* pChannel;
	UINT uLedCount;
	BYTE uPin;
};

}