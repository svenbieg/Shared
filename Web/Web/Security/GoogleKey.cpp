//===============
// GoogleKey.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Json/JsonElement.h"
#include "Network/Https/HttpsClient.h"
#include "Storage/Base64/Base64Helper.h"
#include "Storage/Buffer.h"
#include "GoogleKey.h"

using namespace Json;
using namespace Network::Http;
using namespace Network::Https;
using namespace Security;
using namespace Storage::Base64;

#ifndef _WIN32
#include "Network/Tls/TlsCertificate.h"
using namespace Network::Tls;
#endif


//===========
// Namespace
//===========

namespace Web {
	namespace Security {


//=============
// Certificate
//=============

#ifndef _WIN32

LPCSTR strGoogle=
"-----BEGIN CERTIFICATE-----\r\n"
"MIIaDDCCGPSgAwIBAgIQDBs8pVsxrx8KC+w6nT8k4jANBgkqhkiG9w0BAQsFADBG\r\n"
"MQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExM\r\n"
"QzETMBEGA1UEAxMKR1RTIENBIDFDMzAeFw0yMjA3MDQwODI0NThaFw0yMjA5MjYw\r\n"
"ODI0NTdaMBsxGTAXBgNVBAMMECouZ29vZ2xlYXBpcy5jb20wWTATBgcqhkjOPQIB\r\n"
"BggqhkjOPQMBBwNCAARljLUh2CKoWQ3iEHxoehTjHYk6Q4ATFgmvkVIsXiCErJCy\r\n"
"HmAcjhC+MMcRkKfnI3JG6JVJY0P5+hvIbaeHP1lWo4IX6jCCF+YwDgYDVR0PAQH/\r\n"
"BAQDAgeAMBMGA1UdJQQMMAoGCCsGAQUFBwMBMAwGA1UdEwEB/wQCMAAwHQYDVR0O\r\n"
"BBYEFCEG/yw4YGaUEEX/yCtXkbzPPXXCMB8GA1UdIwQYMBaAFIp0f6+Fze6VzT2c\r\n"
"0OJGFPNxNR0nMGoGCCsGAQUFBwEBBF4wXDAnBggrBgEFBQcwAYYbaHR0cDovL29j\r\n"
"c3AucGtpLmdvb2cvZ3RzMWMzMDEGCCsGAQUFBzAChiVodHRwOi8vcGtpLmdvb2cv\r\n"
"cmVwby9jZXJ0cy9ndHMxYzMuZGVyMIIVmQYDVR0RBIIVkDCCFYyCECouZ29vZ2xl\r\n"
"YXBpcy5jb22CDmdvb2dsZWFwaXMuY29tghZjbG91ZGVuZHBvaW50c2FwaXMuY29t\r\n"
"ghgqLmNsb3VkZW5kcG9pbnRzYXBpcy5jb22CEioucC5nb29nbGVhcGlzLmNvbYIV\r\n"
"Ki5jbGllbnRzNi5nb29nbGUuY29tghQqLmNsaWVudHM2Lmdvb2dsZS5hY4IUKi5j\r\n"
"bGllbnRzNi5nb29nbGUuYWSCFCouY2xpZW50czYuZ29vZ2xlLmFlghQqLmNsaWVu\r\n"
"dHM2Lmdvb2dsZS5hZoIUKi5jbGllbnRzNi5nb29nbGUuYWeCFCouY2xpZW50czYu\r\n"
"Z29vZ2xlLmFpghQqLmNsaWVudHM2Lmdvb2dsZS5hbIIUKi5jbGllbnRzNi5nb29n\r\n"
"bGUuYW2CFCouY2xpZW50czYuZ29vZ2xlLmFzghQqLmNsaWVudHM2Lmdvb2dsZS5h\r\n"
"dIIUKi5jbGllbnRzNi5nb29nbGUuYXqCFCouY2xpZW50czYuZ29vZ2xlLmJhghQq\r\n"
"LmNsaWVudHM2Lmdvb2dsZS5iZYIUKi5jbGllbnRzNi5nb29nbGUuYmaCFCouY2xp\r\n"
"ZW50czYuZ29vZ2xlLmJnghQqLmNsaWVudHM2Lmdvb2dsZS5iaYIUKi5jbGllbnRz\r\n"
"Ni5nb29nbGUuYmqCFCouY2xpZW50czYuZ29vZ2xlLmJzghQqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5idIIUKi5jbGllbnRzNi5nb29nbGUuYnmCFCouY2xpZW50czYuZ29vZ2xl\r\n"
"LmNhghUqLmNsaWVudHM2Lmdvb2dsZS5jYXSCFCouY2xpZW50czYuZ29vZ2xlLmNj\r\n"
"ghQqLmNsaWVudHM2Lmdvb2dsZS5jZIIUKi5jbGllbnRzNi5nb29nbGUuY2aCFCou\r\n"
"Y2xpZW50czYuZ29vZ2xlLmNnghQqLmNsaWVudHM2Lmdvb2dsZS5jaIIUKi5jbGll\r\n"
"bnRzNi5nb29nbGUuY2mCFCouY2xpZW50czYuZ29vZ2xlLmNsghQqLmNsaWVudHM2\r\n"
"Lmdvb2dsZS5jbYIUKi5jbGllbnRzNi5nb29nbGUuY26CFyouY2xpZW50czYuZ29v\r\n"
"Z2xlLmNvLmFvghcqLmNsaWVudHM2Lmdvb2dsZS5jby5id4IXKi5jbGllbnRzNi5n\r\n"
"b29nbGUuY28uY2uCFyouY2xpZW50czYuZ29vZ2xlLmNvLmNyghcqLmNsaWVudHM2\r\n"
"Lmdvb2dsZS5jby5odYIXKi5jbGllbnRzNi5nb29nbGUuY28uaWSCFyouY2xpZW50\r\n"
"czYuZ29vZ2xlLmNvLmlsghcqLmNsaWVudHM2Lmdvb2dsZS5jby5pbYIXKi5jbGll\r\n"
"bnRzNi5nb29nbGUuY28uaW6CFyouY2xpZW50czYuZ29vZ2xlLmNvLmplghcqLmNs\r\n"
"aWVudHM2Lmdvb2dsZS5jby5qcIIXKi5jbGllbnRzNi5nb29nbGUuY28ua2WCFyou\r\n"
"Y2xpZW50czYuZ29vZ2xlLmNvLmtyghcqLmNsaWVudHM2Lmdvb2dsZS5jby5sc4IX\r\n"
"Ki5jbGllbnRzNi5nb29nbGUuY28ubWGCFyouY2xpZW50czYuZ29vZ2xlLmNvLm16\r\n"
"ghcqLmNsaWVudHM2Lmdvb2dsZS5jby5ueoIXKi5jbGllbnRzNi5nb29nbGUuY28u\r\n"
"dGiCFyouY2xpZW50czYuZ29vZ2xlLmNvLnR6ghcqLmNsaWVudHM2Lmdvb2dsZS5j\r\n"
"by51Z4IXKi5jbGllbnRzNi5nb29nbGUuY28udWuCFyouY2xpZW50czYuZ29vZ2xl\r\n"
"LmNvLnV6ghcqLmNsaWVudHM2Lmdvb2dsZS5jby52ZYIXKi5jbGllbnRzNi5nb29n\r\n"
"bGUuY28udmmCFyouY2xpZW50czYuZ29vZ2xlLmNvLnphghcqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5jby56bYIXKi5jbGllbnRzNi5nb29nbGUuY28ueneCGCouY2xpZW50czYu\r\n"
"Z29vZ2xlLmNvbS5hZoIYKi5jbGllbnRzNi5nb29nbGUuY29tLmFnghgqLmNsaWVu\r\n"
"dHM2Lmdvb2dsZS5jb20uYWmCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5hcoIYKi5j\r\n"
"bGllbnRzNi5nb29nbGUuY29tLmF1ghgqLmNsaWVudHM2Lmdvb2dsZS5jb20uYmSC\r\n"
"GCouY2xpZW50czYuZ29vZ2xlLmNvbS5iaIIYKi5jbGllbnRzNi5nb29nbGUuY29t\r\n"
"LmJughgqLmNsaWVudHM2Lmdvb2dsZS5jb20uYm+CGCouY2xpZW50czYuZ29vZ2xl\r\n"
"LmNvbS5icoIYKi5jbGllbnRzNi5nb29nbGUuY29tLmJ5ghgqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5jb20uYnqCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5jb4IYKi5jbGllbnRz\r\n"
"Ni5nb29nbGUuY29tLmN1ghgqLmNsaWVudHM2Lmdvb2dsZS5jb20uY3mCGCouY2xp\r\n"
"ZW50czYuZ29vZ2xlLmNvbS5kb4IYKi5jbGllbnRzNi5nb29nbGUuY29tLmVjghgq\r\n"
"LmNsaWVudHM2Lmdvb2dsZS5jb20uZWeCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5l\r\n"
"dIIYKi5jbGllbnRzNi5nb29nbGUuY29tLmZqghgqLmNsaWVudHM2Lmdvb2dsZS5j\r\n"
"b20uZ2WCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5naIIYKi5jbGllbnRzNi5nb29n\r\n"
"bGUuY29tLmdpghgqLmNsaWVudHM2Lmdvb2dsZS5jb20uZ3KCGCouY2xpZW50czYu\r\n"
"Z29vZ2xlLmNvbS5ndIIYKi5jbGllbnRzNi5nb29nbGUuY29tLmhrghgqLmNsaWVu\r\n"
"dHM2Lmdvb2dsZS5jb20uaXGCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5qbYIYKi5j\r\n"
"bGllbnRzNi5nb29nbGUuY29tLmpvghgqLmNsaWVudHM2Lmdvb2dsZS5jb20ua2iC\r\n"
"GCouY2xpZW50czYuZ29vZ2xlLmNvbS5rd4IYKi5jbGllbnRzNi5nb29nbGUuY29t\r\n"
"LmxighgqLmNsaWVudHM2Lmdvb2dsZS5jb20ubHmCGCouY2xpZW50czYuZ29vZ2xl\r\n"
"LmNvbS5tbYIYKi5jbGllbnRzNi5nb29nbGUuY29tLm10ghgqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5jb20ubXiCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5teYIYKi5jbGllbnRz\r\n"
"Ni5nb29nbGUuY29tLm5hghgqLmNsaWVudHM2Lmdvb2dsZS5jb20ubmaCGCouY2xp\r\n"
"ZW50czYuZ29vZ2xlLmNvbS5uZ4IYKi5jbGllbnRzNi5nb29nbGUuY29tLm5pghgq\r\n"
"LmNsaWVudHM2Lmdvb2dsZS5jb20ubnCCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5u\r\n"
"coIYKi5jbGllbnRzNi5nb29nbGUuY29tLm9tghgqLmNsaWVudHM2Lmdvb2dsZS5j\r\n"
"b20ucGGCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5wZYIYKi5jbGllbnRzNi5nb29n\r\n"
"bGUuY29tLnBnghgqLmNsaWVudHM2Lmdvb2dsZS5jb20ucGiCGCouY2xpZW50czYu\r\n"
"Z29vZ2xlLmNvbS5wa4IYKi5jbGllbnRzNi5nb29nbGUuY29tLnBsghgqLmNsaWVu\r\n"
"dHM2Lmdvb2dsZS5jb20ucHKCGCouY2xpZW50czYuZ29vZ2xlLmNvbS5weYIYKi5j\r\n"
"bGllbnRzNi5nb29nbGUuY29tLnFhghgqLmNsaWVudHM2Lmdvb2dsZS5jb20ucnWC\r\n"
"GCouY2xpZW50czYuZ29vZ2xlLmNvbS5zYYIYKi5jbGllbnRzNi5nb29nbGUuY29t\r\n"
"LnNighgqLmNsaWVudHM2Lmdvb2dsZS5jb20uc2eCGCouY2xpZW50czYuZ29vZ2xl\r\n"
"LmNvbS5zbIIYKi5jbGllbnRzNi5nb29nbGUuY29tLnN2ghgqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5jb20udGqCGCouY2xpZW50czYuZ29vZ2xlLmNvbS50boIYKi5jbGllbnRz\r\n"
"Ni5nb29nbGUuY29tLnRyghgqLmNsaWVudHM2Lmdvb2dsZS5jb20udHeCGCouY2xp\r\n"
"ZW50czYuZ29vZ2xlLmNvbS51YYIYKi5jbGllbnRzNi5nb29nbGUuY29tLnV5ghgq\r\n"
"LmNsaWVudHM2Lmdvb2dsZS5jb20udmOCGCouY2xpZW50czYuZ29vZ2xlLmNvbS52\r\n"
"ZYIYKi5jbGllbnRzNi5nb29nbGUuY29tLnZughQqLmNsaWVudHM2Lmdvb2dsZS5j\r\n"
"doIUKi5jbGllbnRzNi5nb29nbGUuY3qCFCouY2xpZW50czYuZ29vZ2xlLmRlghQq\r\n"
"LmNsaWVudHM2Lmdvb2dsZS5kaoIUKi5jbGllbnRzNi5nb29nbGUuZGuCFCouY2xp\r\n"
"ZW50czYuZ29vZ2xlLmRtghQqLmNsaWVudHM2Lmdvb2dsZS5keoIUKi5jbGllbnRz\r\n"
"Ni5nb29nbGUuZWWCFCouY2xpZW50czYuZ29vZ2xlLmVzghUqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5ldXOCFCouY2xpZW50czYuZ29vZ2xlLmZpghQqLmNsaWVudHM2Lmdvb2ds\r\n"
"ZS5mbYIUKi5jbGllbnRzNi5nb29nbGUuZnKCFSouY2xpZW50czYuZ29vZ2xlLmZy\r\n"
"bIIUKi5jbGllbnRzNi5nb29nbGUuZ2GCFSouY2xpZW50czYuZ29vZ2xlLmdhbIIU\r\n"
"Ki5jbGllbnRzNi5nb29nbGUuZ2WCFCouY2xpZW50czYuZ29vZ2xlLmdnghQqLmNs\r\n"
"aWVudHM2Lmdvb2dsZS5nbIIUKi5jbGllbnRzNi5nb29nbGUuZ22CFCouY2xpZW50\r\n"
"czYuZ29vZ2xlLmdwghQqLmNsaWVudHM2Lmdvb2dsZS5ncoIUKi5jbGllbnRzNi5n\r\n"
"b29nbGUuZ3mCFCouY2xpZW50czYuZ29vZ2xlLmhrghQqLmNsaWVudHM2Lmdvb2ds\r\n"
"ZS5oboIUKi5jbGllbnRzNi5nb29nbGUuaHKCFCouY2xpZW50czYuZ29vZ2xlLmh0\r\n"
"ghQqLmNsaWVudHM2Lmdvb2dsZS5odYIUKi5jbGllbnRzNi5nb29nbGUuaWWCFCou\r\n"
"Y2xpZW50czYuZ29vZ2xlLmltghQqLmNsaWVudHM2Lmdvb2dsZS5pboIWKi5jbGll\r\n"
"bnRzNi5nb29nbGUuaW5mb4IUKi5jbGllbnRzNi5nb29nbGUuaXGCFCouY2xpZW50\r\n"
"czYuZ29vZ2xlLmlyghQqLmNsaWVudHM2Lmdvb2dsZS5pc4IUKi5jbGllbnRzNi5n\r\n"
"b29nbGUuaXSCFyouY2xpZW50czYuZ29vZ2xlLml0LmFvghQqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5qZYIUKi5jbGllbnRzNi5nb29nbGUuam+CFiouY2xpZW50czYuZ29vZ2xl\r\n"
"LmpvYnOCFCouY2xpZW50czYuZ29vZ2xlLmpwghQqLmNsaWVudHM2Lmdvb2dsZS5r\r\n"
"Z4IUKi5jbGllbnRzNi5nb29nbGUua2mCFCouY2xpZW50czYuZ29vZ2xlLmt6ghQq\r\n"
"LmNsaWVudHM2Lmdvb2dsZS5sYYIUKi5jbGllbnRzNi5nb29nbGUubGmCFCouY2xp\r\n"
"ZW50czYuZ29vZ2xlLmxrghQqLmNsaWVudHM2Lmdvb2dsZS5sdIIUKi5jbGllbnRz\r\n"
"Ni5nb29nbGUubHWCFCouY2xpZW50czYuZ29vZ2xlLmx2ghQqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5tZIIUKi5jbGllbnRzNi5nb29nbGUubWWCFCouY2xpZW50czYuZ29vZ2xl\r\n"
"Lm1nghQqLmNsaWVudHM2Lmdvb2dsZS5ta4IUKi5jbGllbnRzNi5nb29nbGUubWyC\r\n"
"FCouY2xpZW50czYuZ29vZ2xlLm1ughQqLmNsaWVudHM2Lmdvb2dsZS5tc4IUKi5j\r\n"
"bGllbnRzNi5nb29nbGUubXWCFCouY2xpZW50czYuZ29vZ2xlLm12ghQqLmNsaWVu\r\n"
"dHM2Lmdvb2dsZS5td4IUKi5jbGllbnRzNi5nb29nbGUubmWCFyouY2xpZW50czYu\r\n"
"Z29vZ2xlLm5lLmpwghUqLmNsaWVudHM2Lmdvb2dsZS5uZXSCFCouY2xpZW50czYu\r\n"
"Z29vZ2xlLm5nghQqLmNsaWVudHM2Lmdvb2dsZS5ubIIUKi5jbGllbnRzNi5nb29n\r\n"
"bGUubm+CFCouY2xpZW50czYuZ29vZ2xlLm5yghQqLmNsaWVudHM2Lmdvb2dsZS5u\r\n"
"dYIYKi5jbGllbnRzNi5nb29nbGUub2ZmLmFpghQqLmNsaWVudHM2Lmdvb2dsZS5w\r\n"
"a4IUKi5jbGllbnRzNi5nb29nbGUucGyCFCouY2xpZW50czYuZ29vZ2xlLnBughQq\r\n"
"LmNsaWVudHM2Lmdvb2dsZS5wc4IUKi5jbGllbnRzNi5nb29nbGUucHSCFCouY2xp\r\n"
"ZW50czYuZ29vZ2xlLnJvghQqLmNsaWVudHM2Lmdvb2dsZS5yc4IUKi5jbGllbnRz\r\n"
"Ni5nb29nbGUucnWCFCouY2xpZW50czYuZ29vZ2xlLnJ3ghQqLmNsaWVudHM2Lmdv\r\n"
"b2dsZS5zY4IUKi5jbGllbnRzNi5nb29nbGUuc2WCFCouY2xpZW50czYuZ29vZ2xl\r\n"
"LnNoghQqLmNsaWVudHM2Lmdvb2dsZS5zaYIUKi5jbGllbnRzNi5nb29nbGUuc2uC\r\n"
"FCouY2xpZW50czYuZ29vZ2xlLnNtghQqLmNsaWVudHM2Lmdvb2dsZS5zboIUKi5j\r\n"
"bGllbnRzNi5nb29nbGUuc2+CFCouY2xpZW50czYuZ29vZ2xlLnNyghQqLmNsaWVu\r\n"
"dHM2Lmdvb2dsZS5zdIIUKi5jbGllbnRzNi5nb29nbGUudGSCFSouY2xpZW50czYu\r\n"
"Z29vZ2xlLnRlbIIUKi5jbGllbnRzNi5nb29nbGUudGeCFCouY2xpZW50czYuZ29v\r\n"
"Z2xlLnRrghQqLmNsaWVudHM2Lmdvb2dsZS50bIIUKi5jbGllbnRzNi5nb29nbGUu\r\n"
"dG2CFCouY2xpZW50czYuZ29vZ2xlLnRughQqLmNsaWVudHM2Lmdvb2dsZS50b4IU\r\n"
"Ki5jbGllbnRzNi5nb29nbGUudHSCFCouY2xpZW50czYuZ29vZ2xlLnVzghQqLmNs\r\n"
"aWVudHM2Lmdvb2dsZS51eoIUKi5jbGllbnRzNi5nb29nbGUudmeCFCouY2xpZW50\r\n"
"czYuZ29vZ2xlLnZ1ghQqLmNsaWVudHM2Lmdvb2dsZS53czAhBgNVHSAEGjAYMAgG\r\n"
"BmeBDAECATAMBgorBgEEAdZ5AgUDMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9j\r\n"
"cmxzLnBraS5nb29nL2d0czFjMy9tb1ZEZklTaWEyay5jcmwwggEFBgorBgEEAdZ5\r\n"
"AgQCBIH2BIHzAPEAdgAFnAHTIOAHhBOVgEmNEXyQMmavr3JQta87RqQ+EYQNSgAA\r\n"
"AYHIhxFYAAAEAwBHMEUCIGWsQMlgT97h1MtF2Fzw2M6iSseoQroaPV2b+lgkV2VA\r\n"
"AiEA195FpI175pR4TUvBEGCubLlQR7MtBE1ChuRmZpXowE8AdwApeb7wnjk5IfBW\r\n"
"c59jpXflvld9nGAK+PlNXSZcJV3HhAAAAYHIhxFMAAAEAwBIMEYCIQDXytBuUff6\r\n"
"VyyyhzzU1d4uY92+vzBJfL4p4faIoYFOyAIhAKEW7blqG3jW0jR3qSrLiN4c8Onc\r\n"
"wrhvfLueomyb/zAFMA0GCSqGSIb3DQEBCwUAA4IBAQA95dfhHLf/n6hLxVKn/hKz\r\n"
"jKgjlBRxhwIDp2e8j8+S4nqajgMIyh3h9WdNcFbhsTNxNA3RLVsYTPxB5ind7gOk\r\n"
"h1gHEarY2xateeQvBUpVf6bGYYTgEsswAfR7v0LfWRpFCi8H8j542D86ZI38IfCZ\r\n"
"UGUeUfx5DipnuAdd3BwTfw5OUEwxCn0F2j07K9Qp1Cu7lKVdnwWZQgGI2Y4w9Fyc\r\n"
"GsTmK3sKLgnoXlWj1a0CnAT9p/JKLV3TfR2iXSSPBdIvkwNnYRaUcVpZMUb2yKeP\r\n"
"S1g39dF3PLgJdHuc0pT3npG3OwZl0kFUO0HLcCwfVBJLGdsyRZhlEX+WTgjbU6JM\r\n"
"-----END CERTIFICATE-----\r\n";
#endif


//==================
// Con-/Destructors
//==================

GoogleKey::GoogleKey(Handle<String> id, Handle<Buffer> exp, Handle<Buffer> mod):
RsaKey(exp, mod),
Id(id)
{
if(!hKeys)
	hKeys=new KeyMap();
hKeys->Set(Id, this);
}


//========
// Common
//========

Handle<GoogleKey> GoogleKey::Get(Handle<String> id)
{
if(!id)
	return nullptr;
Handle<GoogleKey> key;
if(hKeys)
	{
	key=hKeys->Get(id);
	if(key)
		return key;
	hKeys->Clear();
	}
#ifndef _WIN32
TlsCertificate::Add("googleapis.com", strGoogle);
#endif
auto con=HttpsClient::Connect("googleapis.com");
if(!con)
	return nullptr;
Handle<HttpRequest> request=new HttpRequest();
request->Method=HttpMethod::Get;
request->Path="/oauth2/v3/certs";
request->Properties->Add("Host", "www.googleapis.com");
con->Send(request);
auto response=con->GetResponse();
if(!response)
	return nullptr;
if(response->Status!=HttpStatus::Ok)
	return nullptr;
auto json=JsonElement::FromStream(con);
if(!json)
	return nullptr;
auto keys=json->GetList("keys");
if(!keys)
	return nullptr;
for(auto it=keys->First(); it->HasCurrent(); it->MoveNext())
	{
	auto key_json=Convert<JsonElement>(it->GetCurrent());
	if(!key_json)
		return nullptr;
	auto kid=key_json->GetString("kid");
	auto e=key_json->GetString("e");
	auto n=key_json->GetString("n");
	if(!kid||!e||!n)
		return nullptr;
	auto exp=Base64Decode(e->Begin(), 0);
	auto mod=Base64Decode(n->Begin(), 0);
	new GoogleKey(kid, exp, mod);
	}
if(!hKeys)
	return nullptr;
return hKeys->Get(id);
}


//================
// Common Private
//================

Handle<GoogleKey::KeyMap> GoogleKey::hKeys;

}}