//===============
// TlsRandom.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "TlsRandom.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tls {


//==================
// Con-/Destructors
//==================

TlsRandom::TlsRandom():
cContext(),
cEntropy()
{
hCurrent=this;
mbedtls_ctr_drbg_init(&cContext);
mbedtls_entropy_init(&cEntropy);
INT status=mbedtls_ctr_drbg_seed(&cContext, mbedtls_entropy_func, &cEntropy, nullptr, 0);
if(status!=0)
	{
	DebugPrint("TlsRandom: mbedtls_ctr_drbg_seed() failed\n");
	return;
	}
}

TlsRandom::~TlsRandom()
{
mbedtls_ctr_drbg_free(&cContext);
mbedtls_entropy_free(&cEntropy);
}


//========
// Common
//========

Handle<TlsRandom> TlsRandom::Get()
{
if(!hCurrent)
	new TlsRandom();
return hCurrent;
}


//================
// Common Private
//================

Handle<TlsRandom> TlsRandom::hCurrent;

}}