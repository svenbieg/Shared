//==============
// Pressure.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Pressure.h"


//===========
// Namespace
//===========

namespace Physics {


//==================
// Con-/Destructors
//==================

Pressure::Pressure(SHORT hpa):
Pressure(nullptr, hpa)
{}

Pressure::Pressure(Handle<String> hname, SHORT hpa):
TypedVariable(hname, hpa)
{}


//========
// Common
//========

Handle<String> Pressure::ToString()
{
SharedLock lock(cMutex);
if(tValue<0)
	return "-";
return new String("%ihPa", tValue);
}

}
