//=========
// Brush.h
//=========

#pragma once


//=======
// Using
//=======

#include "Graphics/Brush.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//=======
// Brush
//=======

class Brush: public Graphics::Brush
{
public:
	// Con-/Destructors
	Brush(COLOR Color): uColor(Color) {}

	// Common
	COLOR GetColor()const override { return uColor; }

private:
	// Common
	COLOR uColor;
};

}}