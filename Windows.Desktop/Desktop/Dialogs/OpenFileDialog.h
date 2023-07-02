//==================
// OpenFileDialog.h
//==================

#pragma once


//=======
// Using
//=======

#include "Sentence.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Dialogs {


//===========
// Open File
//===========

class OpenFileDialog
{
public:
	// Common
	static Handle<String> Show(Handle<String> Path, Handle<Sentence> Title=nullptr, Handle<Sentence> Filter=nullptr);
};

}}
