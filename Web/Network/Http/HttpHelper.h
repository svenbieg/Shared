//==============
// HttpHelper.h
//==============

#pragma once


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//=============
// HTTP-Status
//=============

enum class HttpStatus: UINT
{
None=0,
Ok=200,
NoContent=204,
MovedPermanently=301,
MovedTemporary=302,
PermanentRedirect=308,
BadRequest=400,
Forbidden=403,
SiteNotFound=404,
RequestTimeout=408,
LengthRequired=411,
ConnectionClosed=444,
InternalServerError=500
};

LPCSTR HttpStatusToString(HttpStatus Status);
HttpStatus HttpStatusFromString(LPCTSTR Status);


//=============
// HTTP-Method
//=============

enum class HttpMethod: UINT
{
Get,
Notify,
Set,
Post,
Unknown
};

LPCSTR HttpMethodToString(HttpMethod Method);
HttpMethod HttpMethodFromString(LPCTSTR Method);


//===========
// HTTP-Path
//===========

UINT HttpPathLength(LPCTSTR Buffer, UINT Length=0);
Handle<String> HttpPathToString(LPCTSTR Buffer, UINT Length=0);

}}
