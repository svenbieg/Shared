//=============
// Console.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Console.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Console {


//==================
// Con-/Destructors
//==================

Console::Console()
{
hInput=GetStdHandle(STD_INPUT_HANDLE);
hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
uCodePage=GetConsoleCP();
}


//========
// Common
//========

Handle<Console> Console::Open()
{
if(!hCurrent)
	hCurrent=new Console();
return hCurrent;
}


//==============
// Input-Stream
//==============

SIZE_T Console::Available()
{
return 0;
}

SIZE_T Console::Read(VOID* buf, SIZE_T size)
{
return 0;
}


//===============
// Output-Stream
//===============

VOID Console::Flush()
{
}

SIZE_T Console::Write(VOID const* buf, SIZE_T size)
{
if(!buf||!size)
	return 0;
DWORD written=0;
#ifdef _UNICODE
LPCWSTR input=(LPCWSTR)buf;
UINT len=size/sizeof(WCHAR);
UINT copy=WideCharToMultiByte(uCodePage, 0, input, len, nullptr, 0, nullptr, nullptr);
LPSTR output=new CHAR[copy];
WideCharToMultiByte(uCodePage, 0, input, len, output, copy, nullptr, nullptr);
WriteConsoleA(hOutput, output, copy, &written, 0);
delete output;
return written;
#else
WriteConsoleA(hOutput, buf, size, &written, 0);
return written;
#endif
}


//================
// Common Private
//================

Handle<Console> Console::hCurrent;

}