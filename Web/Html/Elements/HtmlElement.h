//===============
// HtmlElement.h
//===============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/OutputStream.h"
#include "Web/WebContext.h"


//======================
// Forward-Declarations
//======================

namespace Html
{
class HtmlDocument;
namespace Elements
	{
	class HtmlNode;
	}
}


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//==============
// HTML-Element
//==============

class HtmlElement: public Object
{
public:
	// Using
	using HtmlNode=Elements::HtmlNode;
	using LanguageCode=Culture::LanguageCode;
	using OutputStream=Storage::Streams::OutputStream;
	using WebContext=Web::WebContext;

	// Common
	HtmlDocument* const Document;
	HtmlNode* const Parent;
	virtual SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level=0)=0;

protected:
	// Con-/Destructors
	HtmlElement(HtmlDocument* Document);
	HtmlElement(HtmlNode* Parent);
	HtmlElement(HtmlDocument* Document, HtmlNode* Parent);
};

}}