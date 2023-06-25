//=============
// HtmlLabel.h
//=============

#pragma once


//=======
// Using
//=======

#include "HtmlNode.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//============
// HTML-Label
//============

class HtmlLabel: public HtmlNode
{
public:
	// Con-/Destructors
	HtmlLabel(HtmlNode* Parent, Handle<Sentence> Label, Handle<Sentence> Unit=nullptr);

	// Common
	Handle<Sentence> Label;
	Handle<Sentence> Unit;

protected:
	// Common
	SIZE_T WriteElementsToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;
};

}}