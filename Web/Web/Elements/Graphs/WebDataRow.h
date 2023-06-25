//==============
// WebDataRow.h
//==============

#pragma once


//=======
// Using
//=======

#include "Collections/Vector.h"
#include "Graphics/Color.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {
		namespace Graphs {


//======================
// Forward-Declarations
//======================

class WebGraph;


//=========
// Web-Row
//=========

class WebDataRow: public Object
{
public:
	// Using
	using COLOR=Graphics::COLOR;
	using OutputStream=Storage::Streams::OutputStream;
	using ValueVector=Collections::Vector<INT>;

	// Con-/Destructors
	WebDataRow(WebGraph* Graph, LPCSTR Id, Handle<Sentence> Name, COLOR Color, Handle<ValueVector> Values);

	// Common
	COLOR Color;
	LPCSTR Id;
	Handle<Sentence> Name;
	SIZE_T WriteToStream(OutputStream* Stream, INT Offset=0, UINT Divisor=1, INT Min=INT_MIN, INT Max=INT_MAX-1);
	Handle<ValueVector> Values;
};

}}}