//==========
// TlsKey.h
//==========

#pragma once


//=======
// Using
//=======

#include <mbedtls/ssl.h>
#include "Collections/Map.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tls {


//======================
// Forward-Declarations
//======================

class TlsKey;


//===========
// Key-Store
//===========

typedef Collections::Map<Handle<String>, Handle<TlsKey>> TlsKeyStore;


//=========
// TLS-Key
//=========

class TlsKey: public Object
{
public:
	// Con-/Destructors
	TlsKey(Handle<String> HostName, LPCSTR Key);
	~TlsKey();

	// Common
	mbedtls_pk_context* Get() { return &cKey; }
	static Handle<TlsKeyStore> Store;

private:
	// Common
	mbedtls_pk_context cKey;
};

}}