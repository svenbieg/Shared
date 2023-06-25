//================
// HtmlDocument.h
//================

#pragma once


//=======
// Using
//=======

#include "Elements/HtmlHead.h"


//===========
// Namespace
//===========

namespace Html {


//===============
// HTML-Document
//===============

class HtmlDocument: public Elements::HtmlElement
{
public:
	// Using
	using HtmlHead=Elements::HtmlHead;
	using HtmlNode=Elements::HtmlNode;

	// Con-/Destructors
	HtmlDocument();

	// Common
	inline VOID AddScript(LPCSTR Script) { Head->Script->Add(Script); }
	template <class _owner_t> VOID AddScript(_owner_t* Owner, SIZE_T (_owner_t::*Function)(OutputStream*, WebContext*))
		{
		Head->Script->Add(new MemberFunction<_owner_t, SIZE_T, OutputStream*, WebContext*>(Owner, Function));
		}
	inline VOID AddStyle(Handle<String> Class, LPCSTR Style) { Head->Styles->Add(Class, Style); }
	Handle<HtmlNode> Body;
	Handle<HtmlHead> Head;
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level=0)override;
};

}