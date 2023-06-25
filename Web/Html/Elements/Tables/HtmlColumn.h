//==============
// HtmlColumn.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/OutputStream.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//======================
// Forward-Declarations
//======================

class HtmlTable;


//=============
// HTML-Column
//=============

class HtmlColumn: public Object
{
public:
	// Using
	using OutputStream=Storage::Streams::OutputStream;

	// Con-/Destructors
	HtmlColumn(HtmlTable* Table, LPCSTR Style=nullptr);

	// Common
	LPCSTR Style;
	SIZE_T WriteToStream(OutputStream* Stream, UINT Level);
};

}}}