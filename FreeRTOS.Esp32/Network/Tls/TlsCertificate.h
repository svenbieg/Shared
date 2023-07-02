//==================
// TlsCertificate.h
//==================

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

class TlsCertificate;


//===================
// Certificate-Store
//===================

typedef Collections::Map<Handle<String>, Handle<TlsCertificate>> TlsCertificateStore;


//=================
// TLS-Certificate
//=================

class TlsCertificate: public Object
{
public:
	// Con-/Destructors
	TlsCertificate(Handle<String> HostName, LPCSTR Certificate);
	~TlsCertificate();

	// Common
	static VOID Add(Handle<String> HostName, LPCSTR Certificate);
	mbedtls_x509_crt* Get() { return &cCertificate; }
	static Handle<TlsCertificateStore> Store;

private:
	// Common
	mbedtls_x509_crt cCertificate;
};

}}