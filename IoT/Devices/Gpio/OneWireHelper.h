//=================
// OneWireHelper.h
//=================

#pragma once


//===========
// Namespace
//===========

namespace Devices {
	namespace Gpio {


//========
// Common
//========

BOOL OneWireReadBit(BYTE Pin);
BOOL OneWireReset(BYTE Pin);
VOID OneWireWriteBit(BYTE Pin, BOOL Value);

}}