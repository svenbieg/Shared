//=============
// HtmlTable.h
//=============

#pragma once


//=======
// Using
//=======

#include "Collections/List.h"
#include "Html/Elements/HtmlNode.h"
#include "HtmlCell.h"
#include "HtmlColumn.h"
#include "HtmlRow.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//============
// HTML-Table
//============

class HtmlTable: public HtmlNode
{
public:
	// Using
	using ColumnList=Collections::List<Handle<HtmlColumn>>;

	// Con-/Destructors
	HtmlTable(HtmlNode* Parent);

	// Common
	VOID AddColumn(LPCSTR Style=nullptr);
	Handle<HtmlRow> AddRow();
	Handle<Sentence> Caption;
	Handle<ColumnList> Columns;
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;
};

}}}