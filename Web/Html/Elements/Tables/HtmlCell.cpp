//==============
// HtmlCell.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "HtmlCell.h"
#include "HtmlRow.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//=======
// Types
//=======

LPCSTR strTypes[]={ "td", "th" };


//==================
// Con-/Destructors
//==================

HtmlCell::HtmlCell(HtmlRow* row, HtmlCellType type):
HtmlNode(row, strTypes[(UINT)type])
{}

}}}