//==============
// JavaScript.h
//==============

#pragma once


//=======
// Using
//=======

#include "Collections/List.h"
#include "Storage/Streams/OutputStream.h"
#include "Web/WebContext.h"
#include "Function.h"


//======================
// Forward-Declarations
//======================

namespace Html
{
class HtmlDocument;
}


//===========
// Namespace
//===========

namespace Java {


//=============
// Java-Script
//=============

class JavaScript: public Object
{
public:
	// Using
	using GlobalsList=Collections::List<LPCSTR>;
	using HtmlDocument=Html::HtmlDocument;
	using OutputStream=Storage::Streams::OutputStream;
	using WebContext=Web::WebContext;

	// Types
	typedef Function<SIZE_T, OutputStream*, WebContext*> JavaFunction;
	typedef Collections::List<Handle<JavaFunction>> JavaFunctionList;

	// Con-/Destructors
	JavaScript();

	// Common
	VOID Add(LPCSTR Global);
	VOID Add(Handle<JavaFunction> Function);
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context);

private:
	// Common
	Handle<JavaFunctionList> hFunctions;
	Handle<GlobalsList> hGlobals;
};

}