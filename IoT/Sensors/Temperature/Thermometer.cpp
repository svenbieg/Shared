//=================
// Thermometer.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Thermometer.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//============================
// Con-/Destructors Protected
//============================

Thermometer::Thermometer(Handle<String> hid)
{
Temperature=new Physics::Temperature(hid, -300.f);
}

}}