//==================
// RenderTarget.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "RenderTarget.h"
#include "Font.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//==================
// Con-/Destructors
//==================

RenderTarget::RenderTarget(Handle<Bitmap> bitmap):
ptOffset(0, 0),
rcClip(0, 0, 0, 0),
hBitmap(bitmap)
{}


//========
// Common
//========

VOID RenderTarget::Clip(POINT const& offset, RECT const& clip)
{
ptOffset=offset;
rcClip=clip;
}

VOID RenderTarget::DrawBitmap(RECT const& dst, Handle<Graphics::Bitmap> bmp, RECT const& src)
{
}

VOID RenderTarget::DrawLine(POINT const& from, POINT const& to, Handle<Graphics::Brush> brush, UINT width)
{
}

VOID RenderTarget::DrawPolygon(POINT const* points, UINT count, Handle<Graphics::Brush> brush, UINT width)
{
for(UINT u=0; u+1<count; u++)
	DrawLine(points[u], points[u+1], brush, width);
DrawLine(points[count-1], points[0], brush, width);
}

VOID RenderTarget::DrawRect(RECT const& rc, Handle<Graphics::Brush> brush, UINT width)
{
POINT from(rc.Left, rc.Top);
POINT to(rc.Right, rc.Top);
DrawLine(from, to, brush, width);
from.Set(rc.Left, rc.Top);
to.Set(rc.Left, rc.Bottom);
DrawLine(from, to, brush, width);
from.Set(rc.Right, rc.Top);
to.Set(rc.Right, rc.Bottom);
DrawLine(from, to, brush, width);
from.Set(rc.Left, rc.Bottom);
to.Set(rc.Right, rc.Bottom);
DrawLine(from, to, brush, width);
}

VOID RenderTarget::DrawText(RECT const& rc, FLOAT scale, LPCTSTR text, UINT len)
{
COLOR color=TextColor->GetColor();
if(color.GetAlpha()==0)
	return;
auto font=Convert<Emulation::Font>(Font);
if(!font)
	return;
RECT rc_text(rc);
rc_text+=ptOffset;
RECT rc_clip(rc_text);
rc_clip.SetBounds(rcClip);
if(!rc_clip)
	return;
if(len==0)
	len=StringLength(text);
if(len==0)
	return;
UINT font_size=font->GetSize();
for(UINT u=0; u<len; u++)
	{
	if(rc_text.Left>=rc_clip.Right)
		break;
	BYTE uchar=(BYTE)text[u];
	auto char_info=font->GetCharInfo(uchar);
	auto pchar=char_info->Data;
	UINT char_width=char_info->Size/font_size;
	INT char_left=(INT)rc_text.Left;
	INT char_right=char_left+char_width;
	rc_text.Left=(FLOAT)char_right;
	if(char_right<rc_clip.Left)
		continue;
	for(UINT cy=0; cy<font_size; cy++)
		{
		INT y=(INT)rc_text.Top+cy;
		if(y<rc_clip.Top)
			continue;
		if(y>=rc_clip.Bottom)
			break;
		for(UINT cx=0; cx<char_width; cx++)
			{
			INT x=char_left+cx;
			if(x<rc_clip.Left)
				continue;
			if(x>=rc_clip.Right)
				break;
			if(pchar[cy*char_width+cx])
				hBitmap->SetPixel(x, y, color);
			}
		}
	}
}

VOID RenderTarget::FillPolygon(POINT const* points, UINT count, Handle<Graphics::Brush> brush)
{
DrawPolygon(points, count, brush);
}

VOID RenderTarget::FillRect(RECT const& rc, Handle<Graphics::Brush> brush)
{
COLOR c=Convert<Emulation::Brush>(brush)->GetColor();
if(!c.GetAlpha())
	return;
RECT rc_fill(rc);
rc_fill+=ptOffset;
rc_fill.SetBounds(rcClip);
if(!rc_fill)
	return;
for(INT y=rc_fill.Top; y<rc_fill.Bottom; y++)
	{
	for(INT x=rc_fill.Left; x<rc_fill.Right; x++)
		hBitmap->SetPixel(x, y, c);
	}
}

POINT RenderTarget::GetOffset()
{
POINT pt_clip(rcClip.Left, rcClip.Top);
return pt_clip-ptOffset;
}

SIZE RenderTarget::MeasureText(Handle<Graphics::Font> font, FLOAT scale, LPCTSTR text, UINT len)
{
SIZE size(0, 0);
auto emu_font=Convert<Emulation::Font>(font);
if(!emu_font)
	return size;
UINT font_size=emu_font->GetSize();
size.Height=font_size*scale;
if(!text)
	return size;
if(len==0)
	len=StringLength(text);
if(len==0)
	return size;
for(UINT u=0; u<len; u++)
	{
	auto char_info=emu_font->GetCharInfo((BYTE)CharToChar<CHAR, TCHAR>(text[u]));
	UINT char_width=char_info->Size/font_size;
	size.Width+=char_width;
	}
size.Width*=scale;
return size;
}

VOID RenderTarget::SetPixel(INT left, INT top, COLOR c)
{
left+=ptOffset.Left;
if(left<rcClip.Left||left>=rcClip.Right)
	return;
top+=ptOffset.Top;
if(top<rcClip.Top||top>=rcClip.Bottom)
	return;
hBitmap->SetPixel((INT)left, (INT)top, c);
}

VOID RenderTarget::Unclip()
{
rcClip.Clear();
ptOffset.Clear();
}

}}