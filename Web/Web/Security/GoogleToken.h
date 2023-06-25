//===============
// GoogleToken.h
//===============

#pragma once


//=======
// Using
//=======

#include "Storage/Buffer.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Security {


//==============
// Google-Token
//==============

class GoogleToken: public Object
{
public:
	// Using
	using Buffer=Storage::Buffer;

	// Con-/Destructors
	GoogleToken(LPSTR Response, UINT Length);

	// Common
	Handle<String> Email;
};

}}