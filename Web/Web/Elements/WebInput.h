//============
// WebInput.h
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


//============
// Input-Type
//============

enum class WebInputType
{
Text,
Number,
Password
};


//===========
// Web-Input
//===========

class WebInput: public WebVariable
{
public:
	// Con-/Destructors
	WebInput(HtmlNode* Parent, Handle<Variable> Variable, Handle<String> Id=nullptr, WebInputType InputType=WebInputType::Text);
	~WebInput();

	// Common
	VOID OnNotified(Handle<WebContext> Context)override;
	SIZE_T UpdateToStream(OutputStream* Stream, WebContext* Context)override;

protected:
	// Common
	SIZE_T WriteAttributesToStream(OutputStream* Stream, WebContext* Context)override;

private:
	// Common
	VOID OnVariableChanged();
	Handle<Variable> hVariable;
	WebInputType uInputType;
	UINT64 uTimeChanged;
};

}}