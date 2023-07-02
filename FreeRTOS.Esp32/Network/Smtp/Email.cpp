//===========
// Email.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <mbedtls/base64.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <mbedtls/net_sockets.h>
#include <mbedtls/ssl.h>
#include "Core/Application.h"
#include "Email.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Network {
	namespace Smtp {


//=========
// Outlook
//=========

LPCSTR Server="smtp.office365.com";
LPCSTR Port="587";
LPCSTR Certificate=
"-----BEGIN CERTIFICATE-----\r\n"
"MIIE5jCCA86gAwIBAgIQDxcaSMbyI4CSGM0u1t3A6DANBgkqhkiG9w0BAQsFADBh\r\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\r\n"
"QTAeFw0yMDA5MjUwMDAwMDBaFw0zMDA5MjQyMzU5NTlaMEsxCzAJBgNVBAYTAlVT\r\n"
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxJTAjBgNVBAMTHERpZ2lDZXJ0IENsb3Vk\r\n"
"IFNlcnZpY2VzIENBLTEwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDR\r\n"
"rfaHFHlUJ1fHLwVoPJs8zWfsRRAshPKkR8TZU0JFCbvk/jPB17xGL9GL5re1Z3h8\r\n"
"anC+/bjltlTPTF6suCJ0c1UpCHPIZPfQlQkOeYNQv1/11MybQmGOgAS5QarOThKZ\r\n"
"m6zWxb5bAnO1FqSrcWLUmOpAOYWm9rsv6OeHwov2nDLN7Pg+v4nndCOCS9rqv3Om\r\n"
"JTz9v6nlaP/4MKJgxzsuo/PFfzs7/Q8xoXx0D9C/FMS9aPGl52un35sAfkYlTubo\r\n"
"E/P2BsfUbwsnIEJdYbw/YNJ8lnLJfLCL//lIBVME+iKvt81RXW3dkHQD8DNP9MfA\r\n"
"PlZGR69zIIvcej6j8l3/AgMBAAGjggGuMIIBqjAdBgNVHQ4EFgQU3VHQojFzqXOu\r\n"
"j7QBfl2MV8uf8PcwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUwDgYD\r\n"
"VR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNV\r\n"
"HRMBAf8ECDAGAQH/AgEAMHYGCCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0\r\n"
"cDovL29jc3AuZGlnaWNlcnQuY29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0\r\n"
"cy5kaWdpY2VydC5jb20vRGlnaUNlcnRHbG9iYWxSb290Q0EuY3J0MHsGA1UdHwR0\r\n"
"MHIwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2Jh\r\n"
"bFJvb3RDQS5jcmwwN6A1oDOGMWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdp\r\n"
"Q2VydEdsb2JhbFJvb3RDQS5jcmwwMAYDVR0gBCkwJzAHBgVngQwBATAIBgZngQwB\r\n"
"AgEwCAYGZ4EMAQICMAgGBmeBDAECAzANBgkqhkiG9w0BAQsFAAOCAQEANJE52TD/\r\n"
"zFvmYQGp0P3ntVzclyqsN7Aga/s2SmhGoow32hcBWc6OVgQILYjXndBwRdTn6/97\r\n"
"nb+5a0sEfMoc7mto2ALmLim+XgZ6bg2nQX1A2lWYUoFou0YDHzGsKUNcLQOjoJU4\r\n"
"t9UMxv6+Je7RB77+j3mVmsNxBF13Q+LEHWiY+IJSazVqv7w73izbAFo6cF9sK0hp\r\n"
"qdmSKdB/MNfnT9YF4/WYlyCwFhpaK3mPuU2XiOzGswPhMMRwgawnk4XTNemtHPSq\r\n"
"fP/JzQHsefL75Tx5c8tHJAcp3C/QD+JcUUHocUPuW62x79wO9pNl5N5U4jIVFa4k\r\n"
"x6pNQytYvwMPeg==\r\n"
"-----END CERTIFICATE-----\r\n";


//==================
// Con-/Destructors
//==================

Email::Email()
{}


//========
// Common
//========

VOID Email::Send(Handle<String> server, Handle<String> user, Handle<String> password)
{
if(!From||!To||!Subject||!Text)
	{
	DebugPrint("Email - Missing Parameter\n");
	return;
	}
hCallback=this;
hPassword=password;
hServer=server;
hUser=user;
xTaskCreate(SendProc, "email_task", 12288, this, 5, nullptr);
}


//================
// Common Private
//================

VOID Email::DoAbort(VOID* pssl, VOID* pnet)
{
if(pssl)
	mbedtls_ssl_session_reset((mbedtls_ssl_context*)pssl);
if(pnet)
	mbedtls_net_free((mbedtls_net_context*)pnet);
Application::Current->Dispatch(this, &Email::OnAborted);
}

VOID Email::DoSend()
{
mbedtls_ssl_context ssl;
mbedtls_ssl_init(&ssl);
mbedtls_ctr_drbg_context random;
mbedtls_ctr_drbg_init(&random);
mbedtls_entropy_context entropy;
mbedtls_entropy_init(&entropy);
if(mbedtls_ctr_drbg_seed(&random, mbedtls_entropy_func, &entropy, nullptr, 0)!=0)
	{
	DebugPrint("Email: mbedtls_ctr_drbg_seed()\n");
	DoAbort(nullptr, nullptr);
	return;
	}
mbedtls_x509_crt cert;
mbedtls_x509_crt_init(&cert);
UINT cert_len=StringLength(Certificate)+1;
if(mbedtls_x509_crt_parse(&cert, (BYTE const*)Certificate, cert_len)!=0)
	{
	DebugPrint("Email: mbedtls_x509_crt_parse()\n");
	DoAbort(nullptr, nullptr);
	return;
	}
if(mbedtls_ssl_set_hostname(&ssl, Server)!=0)
	{
	DebugPrint("Email: mbedtls_ssl_set_hostname()\n");
	DoAbort(nullptr, nullptr);
	return;
	}
mbedtls_ssl_config sslcfg;
mbedtls_ssl_config_init(&sslcfg);
if(mbedtls_ssl_config_defaults(&sslcfg, MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT)!=0)
	{
	DebugPrint("Email: mbedtls_ssl_config_defaults()\n");
	DoAbort(nullptr, nullptr);
	return;
	}
mbedtls_ssl_conf_authmode(&sslcfg, MBEDTLS_SSL_VERIFY_REQUIRED);
mbedtls_ssl_conf_ca_chain(&sslcfg, &cert, NULL);
mbedtls_ssl_conf_rng(&sslcfg, mbedtls_ctr_drbg_random, &random);
if(mbedtls_ssl_setup(&ssl, &sslcfg)!=0)
	{
	DebugPrint("Email: mbedtls_ssl_setup()\n");
	DoAbort(nullptr, nullptr);
	return;
	}
mbedtls_net_context net;
mbedtls_net_init(&net);
if(mbedtls_net_connect(&net, Server, Port, MBEDTLS_NET_PROTO_TCP)!=0)
	{
	DebugPrint("Email: mbedtls_net_connect()\n");
	DoAbort(&ssl, nullptr);
	return;
	}
mbedtls_ssl_set_bio(&ssl, &net, mbedtls_net_send, mbedtls_net_recv, NULL);
CHAR pbuf[512];
INT istatus=0;
size_t ulen=ReceiveData(&net, pbuf, 512, &istatus);
if(!ulen||istatus<200||istatus>299)
	{
	DebugPrint("Email: mbedtls_ssl_set_bio()\n");
	DoAbort(&ssl, &net);
	return;
	}
ulen=StringPrint(pbuf, 512, "EHLO esp\r\n");
ulen=SendAndReceive(&net, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<200||istatus>299)
	{
	DebugPrint("Email: EHLO esp\n");
	DoAbort(&ssl, &net);
	return;
	}
ulen=StringPrint(pbuf, 512, "STARTTLS\r\n");
ulen=SendAndReceive(&net, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<200||istatus>299)
	{
	DebugPrint("Email: STARTTLS\n");
	DoAbort(&ssl, &net);
	return;
	}
while((istatus=mbedtls_ssl_handshake(&ssl))!=0)
	{
	if(istatus!=MBEDTLS_ERR_SSL_WANT_READ&&istatus!=MBEDTLS_ERR_SSL_WANT_WRITE)
		{
		UINT res=mbedtls_ssl_get_verify_result(&ssl);
		DebugPrint("Email: mbedtls_ssl_handshake(): %u\n", res);
		DoAbort(&ssl, &net);
		return;
		}
	}
if(mbedtls_ssl_get_verify_result(&ssl)!=0)
	{
	DebugPrint("Email: mbedtls_ssl_get_verify_result()\n");
	DoAbort(&ssl, &net);
	return;
	}
ulen=StringPrint(pbuf, 512, "EHLO esp\r\n");
ulen=SendAndReceiveSsl(&ssl, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<200||istatus>299)
	{
	DebugPrint("Email: EHLO esp\n");
	DoAbort(&ssl, &net);
	return;
	}
ulen=StringPrint(pbuf, 512, "AUTH LOGIN\r\n");
ulen=SendAndReceiveSsl(&ssl, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<200||istatus>399)
	{
	DebugPrint("Email: AUTH LOGIN\n");
	DoAbort(&ssl, &net);
	return;
	}
istatus=mbedtls_base64_encode((BYTE*)pbuf, 128, &ulen, (BYTE const*)hUser->Begin(), hUser->GetLength());
if(istatus!=0)
	{
	DebugPrint("Email: mbedtls_base64_encode() USER\n");
	DoAbort(&ssl, &net);
	return;
	}
pbuf[ulen++]='\r';
pbuf[ulen++]='\n';
pbuf[ulen]=0;
ulen=SendAndReceiveSsl(&ssl, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<300||istatus>399)
	{
	DebugPrint("Email: USER\n");
	DoAbort(&ssl, &net);
	return;
	}
istatus=mbedtls_base64_encode((BYTE*)pbuf, 128, &ulen, (BYTE const*)hPassword->Begin(), hPassword->GetLength());
if(istatus!=0)
	{
	DebugPrint("Email: mbedtls_base64_encode() PASSWD\n");
	DoAbort(&ssl, &net);
	return;
	}
pbuf[ulen++]='\r';
pbuf[ulen++]='\n';
pbuf[ulen]=0;
ulen=SendAndReceiveSsl(&ssl, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<200||istatus>399)
	{
	DebugPrint("Email: PASSWD\n");
	DoAbort(&ssl, &net);
	return;
	}
auto pfrom=From->Begin();
ulen=StringPrint(pbuf, 512, "MAIL FROM:<%s>\r\n", pfrom);
ulen=SendAndReceiveSsl(&ssl, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<200||istatus>299)
	{
	DebugPrint("Email: MAIL FROM\n");
	DoAbort(&ssl, &net);
	return;
	}
auto pto=To->Begin();
ulen=StringPrint(pbuf, 512, "RCPT TO:<%s>\r\n", pto);
ulen=SendAndReceiveSsl(&ssl, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<200||istatus>299)
	{
	DebugPrint("Email: RCPT TO\n");
	DoAbort(&ssl, &net);
	return;
	}
ulen=StringPrint(pbuf, 512, "DATA\r\n");
ulen=SendAndReceiveSsl(&ssl, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<300||istatus>399)
	{
	DebugPrint("Email: DATA\n");
	DoAbort(&ssl, &net);
	return;
	}
auto psubject=Subject->Begin();
ulen=StringPrint(pbuf, 512, "From: %s\r\nSubject: %s\r\nTo: %s\r\n\r\n", pfrom, psubject, pto);
ulen=SendDataSsl(&ssl, pbuf, ulen);
if(!ulen)
	{
	DebugPrint("Email: HEAD\n");
	DoAbort(&ssl, &net);
	return;
	}
auto ptext=Text->Begin();
ulen=Text->GetLength();
ulen=SendDataSsl(&ssl, ptext, ulen);
if(!ulen)
	{
	DebugPrint("Email: MSG\n");
	DoAbort(&ssl, &net);
	return;
	}
ulen=StringPrint(pbuf, 512, "\r\n.\r\n");
ulen=SendAndReceiveSsl(&ssl, pbuf, ulen, 512, &istatus);
if(!ulen||istatus<200||istatus>299)
	{
	DebugPrint("Email: FOOT\n");
	DoAbort(&ssl, &net);
	return;
	}
mbedtls_ssl_close_notify(&ssl);
mbedtls_ssl_session_reset(&ssl);
mbedtls_net_free(&net);
Application::Current->Dispatch(this, &Email::OnSent);
}

VOID Email::OnAborted()
{
Aborted(this);
hCallback=nullptr;
}

VOID Email::OnSent()
{
Sent(this);
hCallback=nullptr;
}

SIZE_T Email::ReceiveData(VOID* pnet, LPSTR pbuf, SIZE_T usize, INT* pstatus)
{
*pstatus=-1;
INT istatus=mbedtls_net_recv((mbedtls_net_context*)pnet, (BYTE*)pbuf, usize);
if(istatus<=0)
	{
	DebugPrint("SmtpClient - mbedtls_net_recv() failed (%i)\n", istatus);
	return 0;
	}
pbuf[istatus]=0;
StringScan(pbuf, "%i", pstatus);
return (SIZE_T)istatus;
}

SIZE_T Email::ReceiveDataSsl(VOID* pssl, LPSTR pbuf, SIZE_T usize, INT* pstatus)
{
*pstatus=-1;
INT istatus=0;
while((istatus=mbedtls_ssl_read((mbedtls_ssl_context*)pssl, (BYTE*)pbuf, usize))<=0)
	{
	if(istatus!=MBEDTLS_ERR_SSL_WANT_READ&&istatus!=MBEDTLS_ERR_SSL_WANT_WRITE)
		{
		DebugPrint("mbedtls_ssl_read() failed (%i)\n", istatus);
		return 0;
		}
	}
pbuf[istatus]=0;
StringScan(pbuf, "%i", pstatus);
return (SIZE_T)istatus;
}

SIZE_T Email::SendAndReceive(VOID* pnet, LPSTR pbuf, SIZE_T usize, SIZE_T ubufsize, INT* pstatus)
{
*pstatus=-1;
if(!SendData(pnet, pbuf, usize))
	return 0;
return ReceiveData(pnet, pbuf, ubufsize, pstatus);
}

SIZE_T Email::SendAndReceiveSsl(VOID* pssl, LPSTR pbuf, SIZE_T usize, SIZE_T ubufsize, INT* pstatus)
{
*pstatus=-1;
if(!SendDataSsl(pssl, pbuf, usize))
	return 0;
return ReceiveDataSsl(pssl, pbuf, ubufsize, pstatus);
}

SIZE_T Email::SendData(VOID* pnet, LPCSTR pbuf, SIZE_T usize)
{
INT istatus=mbedtls_net_send((mbedtls_net_context*)pnet, (BYTE const*)pbuf, usize);
if(istatus<=0)
	return 0;
return (SIZE_T)istatus;
}

SIZE_T Email::SendDataSsl(VOID* pssl, LPCSTR pbuf, SIZE_T usize)
{
INT istatus=0;
while((istatus=mbedtls_ssl_write((mbedtls_ssl_context*)pssl, (BYTE const*)pbuf, usize))<=0)
	{
	if(istatus!= MBEDTLS_ERR_SSL_WANT_READ&&istatus!= MBEDTLS_ERR_SSL_WANT_WRITE)
		return 0;
	}
return (SIZE_T)istatus;
}

VOID Email::SendProc(VOID* param)
{
Handle<Email> email=(Email*)param;
email->DoSend();
vTaskDelete(NULL);
}

}}