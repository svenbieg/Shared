//==============
// Oled128x64.h
//==============

#pragma once


//=======
// Using
//=======

#include "Display.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Displays {


//==============
// OLED-Display
//==============

class Oled128x64: public Display
{
public:
	// Con-/Destructors
	Oled128x64(BYTE Address=0x3C);

	// Common
	VOID Flush()override;

private:
	// Common
	VOID SendCommand(BYTE Command);
	VOID SendCommands(BYTE const* Commands, UINT Count);
	BYTE uAddress;
};

}}