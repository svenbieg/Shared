//============
// WebLabel.h
//============

#pragma once


//=======
// Using
//=======

#include "WebVariable.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//===========
// Web-Label
//===========

class WebLabel: public WebVariable
{
public:
	// Con-/Destructors
	WebLabel(HtmlNode* Parent, Handle<Variable> Variable, Handle<String> Id=nullptr);
	~WebLabel();

	// Common
	SIZE_T UpdateToStream(OutputStream* Stream, WebContext* Context)override;

protected:
	// Common
	SIZE_T WriteElementsToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Common
	VOID OnVariableChanged();
	Handle<Variable> hVariable;
	UINT64 uTimeChanged;
};

}}