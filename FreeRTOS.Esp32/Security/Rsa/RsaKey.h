//==========
// RsaKey.h
//==========

#pragma once


//=======
// Using
//=======

#include <mbedtls/rsa.h>
#include "Storage/Buffer.h"
#include "Storage/StaticBuffer.h"


//===========
// Namespace
//===========

namespace Security {
	namespace Rsa {


//=========
// RSA-Key
//=========

class RsaKey: public Object
{
public:
	// Using
	using Buffer=Storage::Buffer;
	using StaticBuffer=Storage::StaticBuffer;

	// Con-/Destructors
	RsaKey(Handle<Buffer> Exponent, Handle<Buffer> Module);
	~RsaKey();

	// Common
	BOOL Verify(Handle<StaticBuffer> Data, Handle<Buffer> Signature);

private:
	// Common
	mbedtls_rsa_context cKey;
};

}}