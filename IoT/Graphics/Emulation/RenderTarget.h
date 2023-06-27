//================
// RenderTarget.h
//================

#pragma once


//=======
// Using
//=======

#include "Graphics/RenderTarget.h"
#include "Brush.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//===============
// Render-Target
//===============

class RenderTarget: public Graphics::RenderTarget
{
public:
	// Con-/Destructors
	RenderTarget(Handle<Graphics::Bitmap> Bitmap);

	// Common
	VOID Clip(POINT const& Offset, RECT const& Clip)override;
	VOID DrawBitmap(RECT const& Destination, Handle<Graphics::Bitmap> Bitmap, RECT const& Source)override;
	VOID DrawLine(POINT const& From, POINT const& To, Handle<Graphics::Brush> Color, UINT Width=1)override;
	VOID DrawPolygon(POINT const* Points, UINT Count, Handle<Graphics::Brush> Brush, UINT Width=1)override;
	VOID DrawRect(RECT const& Rect, Handle<Graphics::Brush> Brush, UINT Width=1)override;
	VOID DrawText(RECT const& Rect, FLOAT Scale, LPCTSTR Text, UINT Length=0)override;
	VOID FillPolygon(POINT const* Points, UINT Count, Handle<Graphics::Brush> Brush)override;
	VOID FillRect(RECT const& Rect, Handle<Graphics::Brush> Brush)override;
	SIZE MeasureText(Handle<Graphics::Font> Font, FLOAT Scale, LPCTSTR Text, UINT Length=0)override;
	POINT GetOffset()override;
	VOID SetPixel(INT Left, INT Top, COLOR Color);
	VOID Unclip()override;

private:
	// Common
	Handle<Graphics::Bitmap> hBitmap;
	POINT ptOffset;
	RECT rcClip;
};

}}