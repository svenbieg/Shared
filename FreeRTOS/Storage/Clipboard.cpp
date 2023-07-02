//===============
// Clipboard.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Clipboard.h"


//===========
// Namespace
//===========

namespace Storage {


//========
// Common
//========

VOID Clipboard::Clear()
{
hText=nullptr;
}

VOID Clipboard::Copy(Handle<String> text)
{
hText=text;
}

Handle<String> Clipboard::GetText()
{
return hText;
}

BOOL Clipboard::HasText()
{
return hText!=nullptr;
}

Handle<Clipboard> Clipboard::Open()
{
if(!hCurrent)
	hCurrent=new Clipboard();
return hCurrent;
}


//==========================
// Con-/Destructors Private
//==========================

Clipboard::Clipboard()
{}


//================
// Common Private
//================

Handle<Clipboard> Clipboard::hCurrent;

}