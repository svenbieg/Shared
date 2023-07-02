//=============
// TlsRandom.h
//=============

#pragma once


//=======
// Using
//=======

#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>


//===========
// Namespace
//===========

namespace Network {
	namespace Tls {


//============
// TLS-Random
//============

class TlsRandom: public Object
{
public:
	// Con-/Destructors
	TlsRandom();
	~TlsRandom();

	// Common
	static Handle<TlsRandom> Get();
	mbedtls_ctr_drbg_context* GetContext() { return &cContext; }
	mbedtls_entropy_context* GetEntropy() { return &cEntropy; }

private:
	// Common
	mbedtls_ctr_drbg_context cContext;
	mbedtls_entropy_context cEntropy;
	static Handle<TlsRandom> hCurrent;
};

}}