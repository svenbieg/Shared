//============
// RsaKey.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "RsaKey.h"


//===========
// Namespace
//===========

namespace Security {
	namespace Rsa {


//==================
// Con-/Destructors
//==================

RsaKey::RsaKey(Handle<Buffer> exp, Handle<Buffer> mod)
{
mbedtls_rsa_init(&cKey);
int status=mbedtls_rsa_import_raw(&cKey, mod->Begin(), mod->GetSize(), nullptr, 0, nullptr, 0, nullptr, 0, exp->Begin(), exp->GetSize());
if(status!=0)
	{
	DebugPrint("mbedtls_rsa_import_raw() failed %i\n", status);
	return;
	}
mbedtls_rsa_complete(&cKey);
}

RsaKey::~RsaKey()
{
mbedtls_rsa_free(&cKey);
}


//========
// Common
//========

BOOL RsaKey::Verify(Handle<StaticBuffer> data, Handle<Buffer> sig)
{
if(!data||!sig)
	return false;
int status=mbedtls_rsa_pkcs1_verify(&cKey, MBEDTLS_MD_SHA256, data->GetSize(), data->Begin(), sig->Begin());
if(status!=0)
	{
	DebugPrint("mbedtls_rsa_pkcs1_verify() failed %i\n", status);
	return false;
	}
return true;
}

}}