//=============
// Partition.h
//=============

#pragma once


//=======
// Using
//=======

#include "Storage/Database/Database.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//===========
// Partition
//===========

class Partition
{
public:
	// Using
	using Database=Storage::Database::Database;

	// Common
	static Handle<Database> Open();

private:
	// Common
	static Handle<Database> hDatabase;
};

}}