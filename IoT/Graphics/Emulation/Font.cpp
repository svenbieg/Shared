//==========
// Font.cpp
//==========

#include "pch.h"


//=======
// Using
//=======

#include "Font.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//============================
// Con-/Destructors Protected
//============================

Font::Font(UINT size):
uSize(size)
{
ZeroMemory(pCharacters, sizeof(pCharacters));
}

}}