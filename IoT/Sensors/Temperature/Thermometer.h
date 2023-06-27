//===============
// Thermometer.h
//===============

#pragma once


//=======
// Using
//=======

#include "Physics/Temperature.h"


//===========
// Namespace
//===========

namespace Sensors {
	namespace Temperature {


//=============
// Thermometer
//=============

class Thermometer: public Object
{
public:
	// Common
	Handle<Physics::Temperature> Temperature;

protected:
	// Con-/Destructors
	Thermometer(Handle<String> Id);
};

}}
