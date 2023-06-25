//=============
// HtmlRow.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "HtmlRow.h"
#include "HtmlTable.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//==================
// Con-/Destructors
//==================

HtmlRow::HtmlRow(HtmlTable* table):
HtmlNode(table, "tr")
{}


//========
// Common
//========

Handle<HtmlCell> HtmlRow::AddCell(HtmlCellType type)
{
Handle<HtmlCell> cell=new HtmlCell(this, type);
return cell;
}

}}}