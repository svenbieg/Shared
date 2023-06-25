//=============
// HtmlBreak.h
//=============

#pragma once


//=======
// Using
//=======

#include "HtmlElement.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//============
// HTML-Break
//============

class HtmlBreak: public HtmlElement
{
public:
	// Con-/Destructors
	HtmlBreak(HtmlNode* Parent, UINT Count=1);

	// Common
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Common
	UINT uCount;
};

}}