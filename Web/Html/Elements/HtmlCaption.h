//===============
// HtmlCaption.h
//===============

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


//==============
// HTML-Caption
//==============

class HtmlCaption: public HtmlNode
{
public:
	// Con-/Destructors
	HtmlCaption(HtmlNode* Parent, Handle<Sentence> Text);
};

}}