//========
// Font.h
//========

#pragma once


//=======
// Using
//=======

#include "Graphics/Font.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//======
// Font
//======

class Font: public Graphics::Font
{
public:
	// Char-Info
	typedef struct
		{
		const BYTE* Data;
		WORD Size;
		}CHARINFO;

	// Common
	CHARINFO const* GetCharInfo(BYTE Char) { return &pCharacters[Char]; }
	UINT GetSize()const override { return uSize; }

protected:
	// Con-/Destructors
	Font(UINT Size);

	// Common
	CHARINFO pCharacters[256];
	UINT uSize;
};

}}