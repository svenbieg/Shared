//==============
// Humidity.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Humidity.h"


//===========
// Namespace
//===========

namespace Physics {


//==================
// Con-/Destructors
//==================

Humidity::Humidity(CHAR ipercent):
Humidity(nullptr, ipercent)
{}

Humidity::Humidity(Handle<String> hname, CHAR ipercent):
TypedVariable(hname, ipercent)
{}


//========
// Common
//========

Handle<String> Humidity::ToString()
{
SharedLock lock(cMutex);
if(tValue>100)
	return "-";
return new String("%i%%", tValue);
}

}
