//=============
// GoogleKey.h
//=============

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Security/Rsa/RsaKey.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Security {


//============
// Google-Key
//============

class GoogleKey: public ::Security::Rsa::RsaKey
{
public:
	// Using
	using KeyMap=Collections::Map<Handle<String>, Handle<GoogleKey>>;

	// Con-/Destructors
	GoogleKey(Handle<String> Id, Handle<Buffer> Exponent, Handle<Buffer> Module);

	// Common
	static Handle<GoogleKey> Get(Handle<String> Id);
	Handle<String> Id;

private:
	// Common
	static Handle<KeyMap> hKeys;
};

}}