//====================
// NetworkParagraph.h
//====================

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


//===================
// Network-Paragraph
//===================

class NetworkParagraph: public Web::Elements::WebParagraph
{
public:
	// Con-/Destructors
	NetworkParagraph(HtmlNode* Parent);
};

}}