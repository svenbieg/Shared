//============
// HtmlText.h
//============

#pragma once


//=======
// Using
//=======

#include "HtmlElement.h"
#include "Sentence.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//===========
// HTML-Text
//===========

class HtmlText: public HtmlElement
{
public:
	// Con-/Destructors
	HtmlText(HtmlNode* Parent, Handle<Sentence> Text);

	// Common
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Common
	Handle<Sentence> hText;
};

}}