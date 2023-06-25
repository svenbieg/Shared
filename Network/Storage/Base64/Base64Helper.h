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

namespace Storage {
	namespace Base64 {


//========
// Common
//========

Handle<Storage::Buffer> Base64Decode(LPCSTR Input, UINT Length);
Handle<Storage::Buffer> Base64Decode(LPCWSTR Input, UINT Length);
Handle<String> Base64DecodeString(LPCSTR Input, UINT Length);
UINT Base64Decode(LPCSTR Input, UINT InputSize, BYTE* Output, UINT OutputSize);
UINT Base64Encode(VOID const* Input, UINT InputSize, LPSTR Output, UINT OutputSize);

}}