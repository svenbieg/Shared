//============
// HtmlLink.h
//============

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


//===========
// HTML-Link
//===========

class HtmlLink: public HtmlNode
{
public:
	// Con-/Destructors
	HtmlLink(HtmlNode* Parent, Handle<Sentence> Link, Handle<Sentence> Text=nullptr);

	// Common
	Handle<Sentence> Link;

protected:
	// Common
	SIZE_T WriteAttributesToStream(OutputStream* Stream, WebContext* Context)override;
};

}}