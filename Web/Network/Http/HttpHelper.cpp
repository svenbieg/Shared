//================
// HttpHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "CharHelper.h"
#include "HttpHelper.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=============
// HTTP-Status
//=============

HttpStatus HttpStatusFromString(LPCTSTR status)
{
if(StringCompare(status, "Ok", 0, false)==0)
	return HttpStatus::Ok;
if(StringCompare(status, "No Content", 0, false)==0)
	return HttpStatus::NoContent;
if(StringCompare(status, "Moved Permanently", 0, false)==0)
	return HttpStatus::MovedPermanently;
if(StringCompare(status, "Moved Temporary", 0, false)==0)
	return HttpStatus::MovedTemporary;
if(StringCompare(status, "Permanent Redirect", 0, false)==0)
	return HttpStatus::PermanentRedirect;
if(StringCompare(status, "Bad Request", 0, false)==0)
	return HttpStatus::BadRequest;
if(StringCompare(status, "Forbidden", 0, false)==0)
	return HttpStatus::Forbidden;
if(StringCompare(status, "Site Not Found", 0, false)==0)
	return HttpStatus::SiteNotFound;
if(StringCompare(status, "Request Timeout", 0, false)==0)
	return HttpStatus::RequestTimeout;
if(StringCompare(status, "Length Required", 0, false)==0)
	return HttpStatus::LengthRequired;
if(StringCompare(status, "Connection Closed", 0, false)==0)
	return HttpStatus::ConnectionClosed;
if(StringCompare(status, "Internal Server Error", 0, false)==0)
	return HttpStatus::InternalServerError;
return HttpStatus::None;
}

LPCSTR HttpStatusToString(HttpStatus status)
{
switch(status)
	{
	case HttpStatus::Ok:
		return "Ok";
	case HttpStatus::NoContent:
		return "No Content";
	case HttpStatus::MovedPermanently:
		return "Moved Permanently";
	case HttpStatus::MovedTemporary:
		return "Moved Temporary";
	case HttpStatus::PermanentRedirect:
		return "Permanent Redirect";
	case HttpStatus::BadRequest:
		return "Bad Request";
	case HttpStatus::Forbidden:
		return "Forbidden";
	case HttpStatus::SiteNotFound:
		return "Site Not Found";
	case HttpStatus::RequestTimeout:
		return "Request Timeout";
	case HttpStatus::LengthRequired:
		return "Length Required";
	case HttpStatus::ConnectionClosed:
		return "Connection Closed";
	case HttpStatus::InternalServerError:
		return "Internal Server Error";
	default:
		return nullptr;
	}
return nullptr;
}


//=============
// HTTP-Method
//=============

HttpMethod HttpMethodFromString(LPCTSTR method)
{
if(StringCompare(method, "NOTIFY", 0, false)==0)
	return HttpMethod::Notify;
if(StringCompare(method, "GET", 0, false)==0)
	return HttpMethod::Get;
if(StringCompare(method, "SET", 0, false)==0)
	return HttpMethod::Set;
if(StringCompare(method, "POST", 0, false)==0)
	return HttpMethod::Post;
return HttpMethod::Unknown;
}

LPCSTR HttpMethodToString(HttpMethod method)
{
switch(method)
	{
	case HttpMethod::Notify:
		return "NOTIFY";
	case HttpMethod::Get:
		return "GET";
	case HttpMethod::Set:
		return "SET";
	case HttpMethod::Post:
		return "POST";
	case HttpMethod::Unknown:
		return "Unknown";
	}
return nullptr;
}


//===========
// HTTP-Path
//===========

UINT HttpPathLength(LPCTSTR str, UINT len)
{
if(len==0)
	len=UINT_MAX;
UINT ret=0;
for(UINT u=0; u<len; u++)
	{
	if(str[u]==0)
		break;
	if(str[u]=='%')
		u+=2;
	ret++;
	}
return ret;
}

Handle<String> HttpPathToString(LPCTSTR str, UINT len)
{
UINT path_len=HttpPathLength(str, len);
Handle<String> hstr=new String(path_len+1, nullptr);
LPTSTR pdst=(LPTSTR)hstr->Begin();
UINT udst=0;
for(UINT u=0; u<len; u++)
	{
	TCHAR c=str[u];
	if(c=='%')
		{
		c=(BYTE)((CharToHex(str[u+1])<<8)|CharToHex(str[u+2]));
		u+=2;
		if(c=='\303')
			{
			TCHAR c1=str[u+1];
			if(c1=='%')
				{
				c1=(BYTE)((CharToHex(str[u+2])<<8)|CharToHex(str[u+3]));
				if(c1=='\204')
					{
					c='\304'; // Ä
					}
				else if(c1=='\226')
					{
					c='\326'; // Ö
					}
				else if(c1=='\234')
					{
					c='\334'; // Ü
					}
				else if(c1=='\237')
					{
					c='\337'; // ß
					}
				else if(c1=='\244')
					{
					c='\344'; // ä
					}
				else if(c1=='\266')
					{
					c='\366'; // ö
					}
				else if(c1=='\274')
					{
					c='\374'; // ü
					}
				else
					{
					c='_';
					}
				u+=3;
				}
			}
		}
	pdst[udst++]=c;
	}
pdst[udst]=0;
return hstr;
}

}}
