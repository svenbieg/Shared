//==========
// Cursor.h
//==========

#pragma once


//=======
// Using
//=======

#include "Graphics/Cursor.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//========
// Cursor
//========

class Cursor: public Graphics::Cursor
{
public:
	// Con-/Destructors
	Cursor() {}

	// Common
	VOID Set()override {}
};

}}