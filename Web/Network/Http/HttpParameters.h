//==================
// HttpParameters.h
//==================

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Storage/Streams/OutputStream.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=================
// HTTP-Parameters
//=================

class HttpParameters: public Collections::Map<Handle<String>, Handle<String>>
{
public:
	// Using
	using OutputStream=Storage::Streams::OutputStream;

	// Con-/Destructors
	HttpParameters();

	// Common
	VOID Set(LPCTSTR Parameters);
	VOID Set(Handle<String> Key, Handle<String> Value);
	SIZE_T WriteToStream(OutputStream* Stream);
};

}}