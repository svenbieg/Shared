//===============
// HttpRequest.h
//===============

#pragma once


//=======
// Using
//=======

#include "Culture/Language.h"
#include "HttpMessage.h"
#include "HttpParameters.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//==============
// Http-Request
//==============

class HttpRequest: public HttpMessage
{
public:
	// Using
	using LanguageCode=Culture::LanguageCode;

	// Con-/Destructors
	HttpRequest();

	// Common
	VOID Clear()override;
	Handle<HttpParameters> Cookies;
	static Handle<HttpRequest> FromUrl(Handle<String> Url);
	LanguageCode GetLanguage();
	HttpMethod Method;
	Handle<HttpParameters> Parameters;
	Handle<String> Path;
	SIZE_T ReadFromStream(InputStream* Stream)override;
	SIZE_T WriteHeaderToStream(OutputStream* Stream);
	SIZE_T WriteToStream(OutputStream* Stream)override;
};

}}
