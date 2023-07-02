//============
// TlsKey.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include <mbedtls/ctr_drbg.h>
#include "TlsKey.h"
#include "TlsRandom.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tls {


//==================
// Con-/Destructors
//==================

TlsKey::TlsKey(Handle<String> host_name, LPCSTR key):
cKey()
{
mbedtls_pk_init(&cKey);
UINT key_len=StringLength(key)+1;
INT status=mbedtls_pk_parse_key(&cKey, (BYTE const*)key, key_len, nullptr, 0, mbedtls_ctr_drbg_random, nullptr);
if(status!=0)
	{
	DebugPrint("TlsKey: mbedtls_pk_parse_key() failed\n");
	return;
	}
if(!Store)
	Store=new TlsKeyStore();
Store->Set(host_name, this);
}

TlsKey::~TlsKey()
{
mbedtls_pk_free(&cKey);
}


//========
// Common
//========

Handle<TlsKeyStore> TlsKey::Store;

}}