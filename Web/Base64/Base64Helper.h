//================
// Base64Helper.h
//================

#pragma once


//=======
// Using
//=======

#include "Storage/Buffer.h"


//===========
// Namespace
//===========

namespace Base64 {


//========
// Common
//========

Handle<Storage::Buffer> Base64Decode(LPCSTR Input, UINT InputSize);
Handle<String> Base64DecodeString(Handle<String> Input);
Handle<String> Base64DecodeString(LPCSTR Input, UINT InputSize);
UINT Base64Decode(LPCSTR Input, UINT InputSize, BYTE* Output, UINT OutputSize);
UINT Base64Encode(VOID const* Input, UINT InputSize, LPSTR Output, UINT OutputSize);

}