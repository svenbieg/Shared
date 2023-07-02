//=============
// Clipboard.h
//=============

#pragma once


//===========
// Namespace
//===========

namespace Storage {


//===========
// Clipboard
//===========

class Clipboard: public Object
{
public:
	// Common
	VOID Clear();
	VOID Copy(Handle<String> Text);
	Handle<String> GetText();
	BOOL HasText();
	static Handle<Clipboard> Open();

private:
	// Con-/Destructors
	Clipboard();

	// Common
	static Handle<Clipboard> hCurrent;
	Handle<String> hText;
};

}