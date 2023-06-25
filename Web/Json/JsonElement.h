//===============
// JsonElement.h
//===============

#pragma once


//=======
// Using
//=======

#include "Collections/List.h"
#include "Collections/Map.h"
#include "Storage/Streams/InputStream.h"
#include "Storage/Streams/OutputStream.h"


//===========
// Namespace
//===========

namespace Json {


//======
// List
//======

using JsonList=Collections::List<Handle<Object>>;


//==============
// JSON-Element
//==============

class JsonElement: public Object
{
public:
	// Using
	using ElementMap=Collections::Map<Handle<String>, Handle<Object>>;
	using InputStream=Storage::Streams::InputStream;
	using OutputStream=Storage::Streams::OutputStream;

	// Con-/Destructors
	JsonElement();

	// Common
	Handle<ElementMap> Elements;
	static Handle<JsonElement> FromStream(InputStream* Stream);
	static Handle<JsonElement> FromString(Handle<String> String);
	Handle<JsonList> GetList(Handle<String> Key);
	Handle<String> GetString(Handle<String> Key);
	SIZE_T ReadFromStream(InputStream* Stream);
	SIZE_T WriteToStream(OutputStream* Stream) { return WriteToStream(Stream, 0); }
	SIZE_T WriteToStream(OutputStream* Stream, UINT Level);
};

}