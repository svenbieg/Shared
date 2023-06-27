//==========
// Device.h
//==========

#pragma once


//===========
// Namespace
//===========

namespace IoT {
	namespace Devices {


//========
// Device
//========

class Device: public Object
{
public:
	// Common
	Handle<String> Name;

protected:
	// Con-/Destructors
	Device(Handle<String> Name);
};

}}