//===========
// Email.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Network/Tcp/TcpSocket.h"
#include "Network/Tls/TlsSocket.h"
#include "Storage/Base64/Base64Helper.h"
#include "Storage/Streams/StringWriter.h"
#include "Storage/Buffer.h"
#include "Email.h"

using namespace Network::Tcp;
using namespace Network::Tls;
using namespace Storage;
using namespace Storage::Base64;
using namespace Storage::Streams;

#ifndef _WIN32
#include "Network/Tls/TlsCertificate.h"
using namespace Network::Tls;
#endif


//===========
// Namespace
//===========

namespace Network {
	namespace Smtp {


//==============
// Certificates
//==============

#ifndef _WIN32

LPCSTR strOutlook=
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

#endif


//==================
// Con-/Destructors
//==================

Email::Email()
{
#ifndef _WIN32
TlsCertificate::Add("smtp.office365.com", strOutlook);
#endif
}


//========
// Common
//========

VOID Email::Send(Handle<String> server, Handle<String> user, Handle<String> password)
{
CreateTask(this, &Email::DoSend, server, user, password);
}


//================
// Common Private
//================

VOID Email::DoSend(Handle<String> server, Handle<String> user, Handle<String> password)
{
Handle<TcpSocket> tcp_socket=new TcpSocket();
if(!tcp_socket->Connect(server, 587))
	return;
UINT buf_size=512;
Handle<Buffer> buf=new Buffer(buf_size);
LPSTR str=(LPSTR)buf->Begin();
INT status=ReadStatus(tcp_socket, str, buf_size);
ASSERT(status>=200&&status<300);
StringWriter writer(tcp_socket);
writer.Print("EHLO email\r\n");
tcp_socket->Flush();
status=ReadStatus(tcp_socket, str, buf_size);
ASSERT(status>=200&&status<300);
writer.Print("STARTTLS\r\n");
tcp_socket->Flush();
status=ReadStatus(tcp_socket, str, buf_size);
ASSERT(status>=200&&status<300);
Handle<TlsSocket> tls_socket=new TlsSocket(tcp_socket);
BOOL hand_shake=tls_socket->Handshake(server);
ASSERT(hand_shake);
writer.SetStream(tls_socket);
writer.Print("EHLO email\r\n");
tls_socket->Flush();
status=ReadStatus(tls_socket, str, buf_size);
ASSERT(status>=200&&status<300);
writer.Print("AUTH LOGIN\r\n");
tls_socket->Flush();
status=ReadStatus(tls_socket, str, buf_size);
ASSERT(status>=300&&status<400);
Base64Encode(user->Begin(), user->GetLength(), str, buf_size);
writer.Print(str);
tls_socket->Flush();
status=ReadStatus(tls_socket, str, buf_size);
ASSERT(status>=300&&status<400);
Base64Encode(password->Begin(), password->GetLength(), str, buf_size);
writer.Print(str);
tls_socket->Flush();
status=ReadStatus(tls_socket, str, buf_size);
ASSERT(status>=200&&status<300);
writer.Print("MAIL FROM:<");
writer.Print(From);
writer.Print(">\r\n");
tls_socket->Flush();
status=ReadStatus(tls_socket, str, buf_size);
ASSERT(status>=200&&status<300);
writer.Print("RCPT TO:<");
writer.Print(To);
writer.Print(">\r\n");
tls_socket->Flush();
status=ReadStatus(tls_socket, str, buf_size);
ASSERT(status>=200&&status<300);
writer.Print("DATA\r\n");
tls_socket->Flush();
status=ReadStatus(tls_socket, str, buf_size);
ASSERT(status>=300&&status<400);
writer.Print("From: ");
writer.Print(From);
writer.Print("\r\nSubject: ");
writer.Print(Subject);
writer.Print("\r\nTo: ");
writer.Print(To);
writer.Print("\r\n\r\n");
writer.Print(Text);
writer.Print("\r\n.\r\n");
tls_socket->Flush();
status=ReadStatus(tls_socket, str, buf_size);
ASSERT(status>=200&&status<300);
tls_socket->Close();
}

INT Email::ReadStatus(InputStream* stream, LPSTR buf, UINT size)
{
SIZE_T read=stream->Read(buf, size);
buf[read]=0;
INT status=0;
StringScan(buf, "%i", &status);
return status;
}

}}