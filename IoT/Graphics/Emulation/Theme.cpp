//===========
// Theme.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Fonts/SmallFont.h"
#include "Theme.h"

using namespace Graphics::Emulation::Fonts;


//===========
// Namespace
//===========

namespace Graphics {
	namespace Emulation {


//==================
// Con-/Destructors
//==================

Theme::Theme(Themes theme)
{
DefaultCursor=new EmuCursor();
DefaultFont=new SmallFont();
switch(theme)
	{
	case Themes::Dark:
		{
		BorderBrush=new EmuBrush(Colors::LightGray);
		ControlBrush=new EmuBrush(Colors::Black);
		FocusBorderBrush=new EmuBrush(Colors::FocusBorder);
		FocusBrush=new EmuBrush(Colors::Focus);
		GrayTextBrush=new EmuBrush(Colors::Gray);
		HighlightBrush=new EmuBrush(Colors::Highlight);
		HighlightBorderBrush=new EmuBrush(Colors::HighlightBorder);
		InactiveHighlightBrush=new EmuBrush(Colors::Silver);
		LightBorderBrush=new EmuBrush(Colors::Gray);
		LightControlBrush=new EmuBrush(Colors::BlackGray);
		LightTextBrush=new EmuBrush(Colors::Gray);
		TextBrush=new EmuBrush(Colors::White);
		WindowBrush=new EmuBrush(Colors::Black);
		break;
		}
	case Themes::Light:
		{
		BorderBrush=new EmuBrush(Colors::Gray);
		ControlBrush=new EmuBrush(Colors::White);
		FocusBorderBrush=new EmuBrush(Colors::FocusBorder);
		FocusBrush=new EmuBrush(Colors::Focus);
		GrayTextBrush=new EmuBrush(Colors::Gray);
		HighlightBrush=new EmuBrush(Colors::Highlight);
		HighlightBorderBrush=new EmuBrush(Colors::HighlightBorder);
		InactiveHighlightBrush=new EmuBrush(Colors::Silver);
		LightBorderBrush=new EmuBrush(Colors::LightGray);
		LightControlBrush=new EmuBrush(Colors::WhiteGray);
		LightTextBrush=new EmuBrush(Colors::Gray);
		TextBrush=new EmuBrush(Colors::Black);
		WindowBrush=new EmuBrush(Colors::White);
		break;
		}
	case Themes::Monochrome:
		{
		BorderBrush=new EmuBrush(Colors::White);
		ControlBrush=new EmuBrush(Colors::Black);
		FocusBorderBrush=new EmuBrush(Colors::White);
		FocusBrush=new EmuBrush(Colors::Transparent);
		GrayTextBrush=new EmuBrush(Colors::White);
		HighlightBrush=new EmuBrush(Colors::Black);
		HighlightBorderBrush=new EmuBrush(Colors::White);
		InactiveHighlightBrush=new EmuBrush(Colors::Black);
		LightBorderBrush=new EmuBrush(Colors::White);
		LightControlBrush=new EmuBrush(Colors::Black);
		LightTextBrush=new EmuBrush(Colors::White);
		TextBrush=new EmuBrush(Colors::White);
		WindowBrush=new EmuBrush(Colors::Black);
		break;
		}
	}
}


//========
// Common
//========

Handle<Theme> Theme::Get(Themes theme)
{
switch(theme)
	{
	case Themes::Dark:
		{
		if(!Dark)
			Dark=new Theme(theme);
		return Dark;
		}
	case Themes::Light:
		{
		if(!Light)
			Light=new Theme(theme);
		return Light;
		}
	case Themes::Monochrome:
		{
		if(!Monochrome)
			Monochrome=new Theme(theme);
		return Monochrome;
		}
	}
return nullptr;
}

Handle<Theme> Theme::Dark;
Handle<Theme> Theme::Light;
Handle<Theme> Theme::Monochrome;


//=========
// Brushes
//=========

Handle<Graphics::Brush> Theme::GetBrush(COLOR c)
{
return new EmuBrush(c);
}

}}