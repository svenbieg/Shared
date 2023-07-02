//===================
// SystemParagraph.h
//===================

#pragma once


//=======
// Using
//=======

#include "Web/Elements/WebParagraph.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Templates {


//==================
// System-Paragraph
//==================

class SystemParagraph: public Web::Elements::WebParagraph
{
public:
	// Con-/Destructors
	SystemParagraph(HtmlNode* Parent);
};

}}