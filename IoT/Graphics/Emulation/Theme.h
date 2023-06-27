//=========
// Theme.h
//=========

#pragma once


//=======
// Using
//=======

#include "Graphics/Emulation/Brush.h"
#include "Graphics/Emulation/Cursor.h"
#include "Graphics/Emulation/Font.h"
#include "Graphics/Theme.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//========
// Themes
//========

enum class Themes
{
Dark,
Light,
Monochrome
};


//=======
// Theme
//=======

class Theme: public Graphics::Theme
{
public:
	// Using
	using EmuBrush=Graphics::Emulation::Brush;
	using EmuCursor=Graphics::Emulation::Cursor;
	using EmuFont=Graphics::Emulation::Font;

	// Con-/Destructors
	Theme(Themes Theme=Themes::Light);

	// Common
	static Handle<Theme> Get(Themes Theme=Themes::Light);
	static Handle<Theme> Dark;
	static Handle<Theme> Light;
	static Handle<Theme> Monochrome;

	// Brushes
	inline Handle<Brush> GetBorderBrush()override { return BorderBrush; }
	Handle<Brush> GetBrush(COLOR Color)override;
	inline Handle<Brush> GetControlBrush()override { return ControlBrush; }
	inline Handle<Brush> GetFocusBorderBrush()override { return FocusBrush; }
	inline Handle<Brush> GetFocusBrush()override { return FocusBorderBrush; }
	inline Handle<Brush> GetGrayTextBrush()override { return GrayTextBrush; }
	inline Handle<Brush> GetHighlightBorderBrush()override { return HighlightBorderBrush; }
	inline Handle<Brush> GetHighlightBrush()override { return HighlightBrush; }
	inline Handle<Brush> GetInactiveHighlightBrush()override { return InactiveHighlightBrush; }
	inline Handle<Brush> GetLightBorderBrush()override { return LightBorderBrush; }
	inline Handle<Brush> GetLightControlBrush()override { return LightControlBrush; }
	inline Handle<Brush> GetLightTextBrush()override { return LightTextBrush; }
	inline Handle<Brush> GetTextBrush()override { return TextBrush; }
	inline Handle<Brush> GetWindowBrush()override { return WindowBrush; }
	Handle<EmuBrush> BorderBrush;
	Handle<EmuBrush> ControlBrush;
	Handle<EmuBrush> FocusBorderBrush;
	Handle<EmuBrush> FocusBrush;
	Handle<EmuBrush> GrayTextBrush;
	Handle<EmuBrush> HighlightBorderBrush;
	Handle<EmuBrush> HighlightBrush;
	Handle<EmuBrush> InactiveHighlightBrush;
	Handle<EmuBrush> LightBorderBrush;
	Handle<EmuBrush> LightControlBrush;
	Handle<EmuBrush> LightTextBrush;
	Handle<EmuBrush> TextBrush;
	Handle<EmuBrush> WindowBrush;

	// Fonts
	inline Handle<Font> GetDefaultFont()override { return DefaultFont; }
	Handle<EmuFont> DefaultFont;

	// Cursors
	inline Handle<Cursor> GetDefaultCursor()override { return DefaultCursor; }
	inline Handle<Cursor> GetHandPointCursor()override { return DefaultCursor; }
	inline Handle<Cursor> GetSizeHorizontalCursor()override { return DefaultCursor; }
	inline Handle<Cursor> GetSizeVerticalCursor()override { return DefaultCursor; }
	inline Handle<Cursor> GetTextCursor()override { return DefaultCursor; }
	Handle<EmuCursor> DefaultCursor;
};

}}