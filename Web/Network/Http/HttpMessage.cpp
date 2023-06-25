//=================
// HttpMessage.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "HttpMessage.h"

using namespace Storage;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//========
// Common
//========

VOID HttpMessage::Clear()
{
Content=nullptr;
Properties->Clear();
Status=HttpStatus::Ok;
}

BOOL HttpMessage::KeepAlive()
{
auto con=Properties->Get("Connection");
if(!con)
	return false;
return StringCompare(con->Begin(), "keep-alive", 0, false)==0;
}

VOID HttpMessage::KeepAlive(BOOL keep_alive)
{
Properties->Set("Connection", keep_alive? "Keep-Alive": "Close");
}


//============================
// Con-/Destructors Protected
//============================

HttpMessage::HttpMessage(HttpStatus status):
Status(status)
{
Properties=new PropertyMap();
}

}}