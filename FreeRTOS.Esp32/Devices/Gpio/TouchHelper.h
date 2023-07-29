//===============
// TouchHelper.h
//===============

#pragma once


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//========
// Common
//========

VOID TouchClose(BYTE Pin);
BOOL TouchInit(BYTE Pin);
UINT TouchRead(BYTE Pin);
VOID TouchTreshold(BYTE Pin, UINT Treshold);

}}