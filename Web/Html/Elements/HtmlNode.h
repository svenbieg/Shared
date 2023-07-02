//============
// HtmlNode.h
//============

#pragma once


//=======
// Using
//=======

#include "Collections/List.h"
#include "Collections/Map.h"
#include "HtmlElement.h"
#include "Sentence.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//=======
// Flags
//=======

enum class HtmlNodeFlags: UINT
{
None=0,
MultiLine=1
};


//===========
// HTML-Node
//===========

class HtmlNode: public HtmlElement
{
public:
	// Using
	using AttributeMap=Collections::Map<Handle<String>, LPCSTR>;
	using ElementList=Collections::List<Handle<HtmlElement>>;

	// Con-/Destructors
	HtmlNode(HtmlDocument* Document, LPCSTR Tag, Handle<String> Id=nullptr);
	HtmlNode(HtmlNode* Parent, LPCSTR Tag, Handle<String> Id=nullptr);

	// Common
	VOID Add(Handle<Sentence> Element);
	Handle<AttributeMap> Attributes;
	VOID Break(UINT Count=1) { uBreaks=Count; }
	Handle<String> Class;
	Handle<ElementList> Elements;
	Handle<String> Id;
	VOID SetFlag(HtmlNodeFlags Flag, BOOL Set=true);
	Handle<String> Style;
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

protected:
	// Con-/Destructors
	HtmlNode(HtmlDocument* Document, HtmlNode* Parent, LPCSTR Tag, Handle<String> Id);

	// Common
	virtual SIZE_T WriteAttributesToStream(OutputStream* Stream, WebContext* Context);
	SIZE_T WriteClosureToStream(OutputStream* Stream, UINT Level);
	virtual SIZE_T WriteElementsToStream(OutputStream* Stream, WebContext* Context, UINT Level);
	SIZE_T WriteTagToStream(OutputStream* Stream, UINT Level);
	LPCSTR pTag;
	UINT uBreaks;
	HtmlNodeFlags uFlags;
};

}}