//====================
// ShellCommandList.h
//====================

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"


//===========
// Namespace
//===========

namespace Runtime {


//======================
// Forward-Declarations
//======================

class Shell;


//====================
// Shell-Command-List
//====================

class ShellCommandList: public Collections::Map<Handle<String>, std::function<VOID(Shell*)>>
{
public:
	// Con-/Destructors
	ShellCommandList();

	// Common
	static Handle<ShellCommandList> Get();

private:
	// Common
	static Handle<ShellCommandList> hCurrent;
};

}