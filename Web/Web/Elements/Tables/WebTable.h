//============
// WebTable.h
//============

#pragma once


//=======
// Using
//=======

#include "Html/Elements/Tables/HtmlTable.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {
		namespace Tables {


//===========
// Web-Table
//===========

class WebTable: public Html::Elements::Tables::HtmlTable
{
public:
	// Using
	using HtmlRow=Html::Elements::Tables::HtmlRow;

	// Con-/Destructors
	WebTable(HtmlNode* Parent);

	// Common
	VOID AddRow(Handle<Sentence> Header, Handle<Sentence> Value);
	VOID AddRow(Handle<Sentence> Header, Handle<Variable> Variable, Handle<String> Id);
};

}}}