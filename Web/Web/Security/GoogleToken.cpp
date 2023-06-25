//=================
// GoogleToken.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Json/JsonElement.h"
#include "Storage/Base64/Base64Helper.h"
#include "Storage/StaticBuffer.h"
#include "GoogleKey.h"
#include "GoogleToken.h"

using namespace Json;
using namespace Storage;
using namespace Storage::Base64;


//===========
// Namespace
//===========

namespace Web {
	namespace Security {


//==================
// Con-/Destructors
//==================

GoogleToken::GoogleToken(LPSTR response, UINT len)
{
LPSTR str=response;
UINT pos=0;
if(!StringFind(str, "credential=", &pos, false))
	return;
str+=pos+11;
LPSTR content_ptr=str;
UINT content_len=0;
if(!StringFindChar(str, '.', &pos, false))
	return;
LPSTR header_ptr=str;
UINT header_len=pos;
content_len+=pos+1;
str+=pos+1;
if(!StringFindChar(str, '.', &pos, false))
	return;
LPSTR body_ptr=str;
UINT body_len=pos;
content_len+=pos;
str+=pos+1;
LPSTR signature_ptr=str;
UINT signature_len=0;
while(signature_ptr[signature_len])
	{
	if(signature_ptr[signature_len]=='&')
		break;
	signature_len++;
	}
auto header_str=Base64DecodeString(header_ptr, header_len);
auto body_str=Base64DecodeString(body_ptr, body_len);
auto signature_buf=Base64Decode(signature_ptr, signature_len);
if(!header_str||!body_str||!signature_buf)
	return;
auto header_json=JsonElement::FromString(header_str);
if(!header_json)
	return;
auto key_id=header_json->GetString("kid");
auto key=GoogleKey::Get(key_id);
if(!key)
	return;
Handle<StaticBuffer> content_buf=new StaticBuffer(content_ptr, content_len);
if(!key->Verify(content_buf, signature_buf))
	return;
auto body_json=JsonElement::FromString(body_str);
if(!body_json)
	return;
Email=body_json->GetString("email");
}

}}