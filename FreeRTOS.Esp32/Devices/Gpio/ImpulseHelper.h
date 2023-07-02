//=================
// ImpulseHelper.h
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

VOID ImpulseClear(BYTE Pin);
VOID ImpulseClose(BYTE Pin);
UINT ImpulseCount(BYTE Pin);
VOID ImpulseInit(BYTE Pin);

}}