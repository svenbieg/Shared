//===========
// Display.h
//===========

#pragma once


//=======
// Using
//=======

#include "Graphics/Emulation/RenderTarget.h"
#include "Graphics/Theme.h"
#include "UI/Frame.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Displays {


//=========
// Display
//=========

class Display: public Object
{
protected:
	// Using
	using Bitmap=Graphics::Bitmap;
	using RECT=Graphics::RECT;
	using RenderTarget=Graphics::Emulation::RenderTarget;

public:
	// Common
	Handle<UI::Frame> UIFrame;
	virtual VOID Flush()=0;

protected:
	// Con-/Destructors
	Display(UINT Width, UINT Height, WORD BitsPerPixel, Handle<Graphics::Theme> Theme);

	// Common
	Handle<Bitmap> hBitmap;

private:
	// Common
	VOID OnFrameInvalidated();
	VOID Render();
	Handle<RenderTarget> hRenderTarget;
};

}}