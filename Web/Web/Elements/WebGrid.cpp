//=============
// WebGrid.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "WebGrid.h"

using namespace Html::Elements::Tables;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//==================
// Con-/Destructors
//==================

WebGrid::WebGrid(HtmlNode* parent):
HtmlTable(parent)
{
Document->AddStyle("table.grid", "border:0; border-collapse:collapse;");
Document->AddStyle("table.grid td", "padding:0;");
Class="grid";
}


//========
// Common
//========

Handle<WebButton> WebGrid::AddButton(Handle<String> id, Handle<Sentence> text)
{
Document->AddStyle("table.grid button", "margin-right:8px; margin-top:8px;");
if(Elements->GetCount()==0)
	new HtmlRow(this);
auto row=Convert<HtmlRow>(Elements->GetAt(0));
auto cell=new HtmlCell(row);
return new WebButton(cell, id, text);
}

}}