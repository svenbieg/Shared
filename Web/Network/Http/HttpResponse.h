//================
// HttpResponse.h
//================

#pragma once


//=======
// Using
//=======

#include "HttpMessage.h"
#include "HttpParameters.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//===============
// Http-Response
//===============

class HttpResponse: public HttpMessage
{
public:
	// Con-/Destructors
	HttpResponse(HttpStatus Status=HttpStatus::Ok);

	// Common
	VOID Clear()override;
	Handle<HttpParameters> Cookies;
	SIZE_T ReadFromStream(InputStream* Stream)override;
	SIZE_T WriteHeaderToStream(OutputStream* Stream);
	SIZE_T WriteToStream(OutputStream* Stream)override;
};

}}