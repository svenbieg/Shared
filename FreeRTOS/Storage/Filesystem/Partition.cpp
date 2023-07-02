//===============
// Partition.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Devices/Storage/FlashDevice.h"
#include "Partition.h"

using namespace Devices::Storage;


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//======================
// Forward-Declarations
//======================

using Database=Storage::Database::Database;


//========
// Common
//========

Handle<Database> Partition::Open()
{
if(!hDatabase)
	{
	auto flash=FlashDevice::Open();
	hDatabase=new Database(flash);
	}
return hDatabase;
}


//================
// Common Private
//================

Handle<Database> Partition::hDatabase;

}}