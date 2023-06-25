//============
// HtmlHead.h
//============

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Java/JavaScript.h"
#include "HtmlNode.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//===========
// HTML-Head
//===========

class HtmlHead: public HtmlNode
{
public:
	// Using
	using JavaScript=Java::JavaScript;
	using StyleList=Collections::Map<Handle<String>, LPCSTR>;

	// Con-/Destructors
	HtmlHead(HtmlDocument* Document);

	// Common
	LPCSTR Icon;
	Handle<JavaScript> Script;
	Handle<StyleList> Styles;
	Handle<Sentence> Title;
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level=0)override;
	Event<HtmlHead, OutputStream*, SIZE_T&, LanguageCode> WritingScript;
};

}}