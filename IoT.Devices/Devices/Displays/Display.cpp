//=============
// Display.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Core/Application.h"
#include "Display.h"

using namespace Core;
using namespace Graphics;


//===========
// Namespace
//===========

namespace Devices {
	namespace Displays {


//============================
// Con-/Destructors Protected
//============================

Display::Display(UINT width, UINT height, WORD bpp, Handle<Graphics::Theme> theme)
{
hBitmap=new Bitmap(width, height, bpp);
hRenderTarget=new RenderTarget(hBitmap);
UIFrame=new UI::Frame(hRenderTarget, theme);
UIFrame->Invalidated.Add(this, &Display::OnFrameInvalidated);
}


//================
// Common Private
//================

VOID Display::OnFrameInvalidated()
{
Application::Current->Dispatch(this, &Display::Render);
}

VOID Display::Render()
{
RECT rc(hBitmap->GetDimensions());
UIFrame->Move(rc);
UIFrame->Render(hRenderTarget);
this->Flush();
}

}}