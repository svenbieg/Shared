//==============
// WebLabel.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "Web/WebPage.h"
#include "WebLabel.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//==================
// Con-/Destructors
//==================

WebLabel::WebLabel(HtmlNode* parent, Handle<Variable> var, Handle<String> id):
WebVariable(parent, "label", id? id: var->Name),
hVariable(var),
uTimeChanged(0)
{
hVariable->Changed.Add(this, &WebLabel::OnVariableChanged);
}

WebLabel::~WebLabel()
{
hVariable->Changed.Remove(this);
}


//========
// Common
//========

SIZE_T WebLabel::UpdateToStream(OutputStream* stream, WebContext* context)
{
if(context->TimeStamp>uTimeChanged)
	return 0;
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print(Id);
size+=writer.Print("=");
size+=writer.Print(hVariable->ToString(lng));
size+=writer.Print(";");
return size;
}


//==================
// Common Protected
//==================

SIZE_T WebLabel::WriteElementsToStream(OutputStream* stream, WebContext* context, UINT level)
{
auto lng=context->Language;
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print(hVariable->ToString(lng));
size+=WebVariable::WriteElementsToStream(stream, context, level);
return size;
}


//================
// Common Private
//================

VOID WebLabel::OnVariableChanged()
{
uTimeChanged=GetTickCount64();
Page->Changed(Page);
}

}}