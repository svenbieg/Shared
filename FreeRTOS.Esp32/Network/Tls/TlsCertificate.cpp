//====================
// TlsCertificate.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "TlsCertificate.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tls {


//==================
// Con-/Destructors
//==================

TlsCertificate::TlsCertificate(Handle<String> host_name, LPCSTR cert):
cCertificate()
{
mbedtls_x509_crt_init(&cCertificate);
UINT cert_len=StringLength(cert)+1;
if(mbedtls_x509_crt_parse(&cCertificate, (BYTE const*)cert, cert_len)!=0)
	{
	DebugPrint("TlsCertificate: mbedtls_x509_crt_parse() failed\n");
	return;
	}
if(!Store)
	Store=new TlsCertificateStore();
Store->Set(host_name, this);
}

TlsCertificate::~TlsCertificate()
{
mbedtls_x509_crt_free(&cCertificate);
}


//========
// Common
//========

VOID TlsCertificate::Add(Handle<String> host_name, LPCSTR cert)
{
if(Store->Get(host_name))
	return;
new TlsCertificate(host_name, cert);
}

Handle<TlsCertificateStore> TlsCertificate::Store;

}}