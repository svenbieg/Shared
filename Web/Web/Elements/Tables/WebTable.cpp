//==============
// WebTable.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Html/Elements/HtmlText.h"
#include "Html/HtmlDocument.h"
#include "Web/Elements/WebLabel.h"
#include "WebTable.h"

using namespace Html::Elements;
using namespace Html::Elements::Tables;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {
		namespace Tables {


//==================
// Con-/Destructors
//==================

WebTable::WebTable(HtmlNode* parent):
HtmlTable(parent)
{
Document->AddStyle("table.simple", "border:1px solid #808080; border-collapse:collapse;");
Document->AddStyle("table.simple td", "border:1px solid #A0A0A0; padding-left:4px; padding-right:4px; text-align:right; vertical-align:middle;");
Document->AddStyle("table.simple th", "background-color:#F8F8F8; border:1px solid #A0A0A0; font-weight:normal; padding-left:4px; padding-right:8px; text-align:left; vertical-align:middle;");
Class="simple";
uBreaks=1;
}


//========
// Common
//========

VOID WebTable::AddRow(Handle<Sentence> header, Handle<Sentence> value)
{
auto row=new HtmlRow(this);
auto th=new HtmlCell(row, HtmlCellType::Header);
new HtmlText(th, header);
auto td=new HtmlCell(row);
new HtmlText(td, value);
}

VOID WebTable::AddRow(Handle<Sentence> header, Handle<Variable> var, Handle<String> id)
{
if(!id)
	id=var->Name;
auto row=new HtmlRow(this);
auto th=new HtmlCell(row, HtmlCellType::Header);
new HtmlText(th, header);
auto td=new HtmlCell(row);
new WebLabel(td, var, id);
}

}}}