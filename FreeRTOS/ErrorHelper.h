//===============
// ErrorHelper.h
//===============

#pragma once


//=======
// Using
//=======

#include <cstdlib>
#include "StringHelper.h"


//========
// Common
//========


#ifdef _DEBUG

VOID DebugPrint(LPCSTR Text);

template <class... _args_t> VOID DebugPrint(LPCSTR Format, _args_t... Arguments)
{
CHAR text[64];
StringPrint(text, 64, Format, Arguments... );
DebugPrint(text);
}

#define ASSERT(Condition) if(!(Condition)){ DebugPrint("%s:%u ASSERT\n", (LPCSTR)__FILE__, (UINT)__LINE__); throw std::exception(); }
#else

#define DebugPrint(...)
#define ASSERT(Condition)

#endif
