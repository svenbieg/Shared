//============
// WebGraph.h
//============

#pragma once


//=======
// Using
//=======

#include "Collections/List.h"
#include "Html/Elements/HtmlNode.h"
#include "WebAxis.h"
#include "WebDataRow.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {
		namespace Graphs {


//===========
// Web-Graph
//===========

class WebGraph: public Html::Elements::HtmlNode
{
public:
	// Using
	using COLOR=Graphics::COLOR;
	using RowList=Collections::List<Handle<WebDataRow>>;
	using ValueVector=WebDataRow::ValueVector;

	// Con-/Destructors
	WebGraph(HtmlNode* Parent, Handle<String> Id);

	// Common
	VOID AddRow(LPCSTR Id, Handle<Sentence> Name, COLOR Color, Handle<ValueVector> Values);
	Handle<WebAxis> AxisX;
	Handle<WebAxis> AxisY;
	UINT Divisor;
	COLOR GridColor;
	INT Offset;
	Handle<RowList> Rows;

private:
	// Common
	SIZE_T WriteScriptToStream(OutputStream* Stream, WebContext* Context);
};

}}}