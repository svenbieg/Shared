//=============
// HtmlImage.h
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
// HTML-Image
//============

class HtmlImage: public HtmlNode
{
public:
	// Con-/Destructors
	HtmlImage(HtmlNode* Parent, Handle<Sentence> Url);

protected:
	// Common
	SIZE_T WriteAttributesToStream(OutputStream* Stream, WebContext* Context)override;

private:
	// Common
	Handle<Sentence> hUrl;
};

}}