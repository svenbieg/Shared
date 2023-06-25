//=========
// Url.cpp
//=========

#include "pch.h"


//=======
// Using
//=======

#include "Url.h"


//========
// Common
//========

Handle<String> Url::Decode(Handle<String> url)
{
if(!url)
	return nullptr;
BOOL escape=false;
UINT len=Decode(nullptr, 0, url->Begin(), &escape);
if(!len)
	return nullptr;
if(!escape)
	return url;
Handle<String> str=new String(len, nullptr);
LPTSTR str_ptr=const_cast<LPTSTR>(str->Begin());
Decode(str_ptr, len+1, url->Begin());
return str;
}

UINT Url::Decode(LPTSTR buf, UINT max, LPCTSTR url, BOOL* escape_ptr)
{
if(!url)
	return 0;
if(!buf)
	max=-1;
BOOL escape=false;
UINT buf_pos=0;
UINT url_pos=0;
while(url[url_pos])
	{
	if(buf_pos+1>max)
		{
		buf_pos=0;
		break;
		}
	if(CharCompare(url[url_pos], '%')==0)
		{
		escape=true;
		UINT hex=0;
		if(StringScan(&url[url_pos+1], "%x", &hex)!=1)
			{
			buf_pos=0;
			break;
			}
		if(buf)
			{
			CHAR c=(CHAR)hex;
			buf[buf_pos]=CharToChar<TCHAR, CHAR>(c);
			}
		buf_pos++;
		url_pos+=3;
		continue;
		}
	if(buf)
		buf[buf_pos]=url[url_pos];
	buf_pos++;
	url_pos++;
	}
if(buf)
	buf[buf_pos]=0;
if(escape_ptr)
	*escape_ptr=escape;
return buf_pos;
}
