//====================
// HttpParameters.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "Clusters/map.hpp"
#include "Storage/Streams/StringWriter.h"
#include "HttpParameters.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//==================
// Con-/Destructors
//==================

HttpParameters::HttpParameters()
{}


//========
// Common
//========

VOID HttpParameters::Set(LPCTSTR params)
{
cMap.clear();
LPCTSTR str=params;
while(1)
	{
	while(str[0]==' ')
		str++;
	UINT pos=0;
	if(!StringFindChar(str, '=', &pos))
		break;
	Handle<String> key=new String(pos, str);
	str+=pos+1;
	if(StringFindChar(str, '&', &pos))
		{
		Handle<String> value=new String(pos, str);
		str+=pos+1;
		cMap.set(key, value);
		continue;
		}
	Handle<String> value=new String(str);
	cMap.set(key, value);
	break;
	}
}

VOID HttpParameters::Set(Handle<String> key, Handle<String> value)
{
Map::Set(key, value);
}

SIZE_T HttpParameters::WriteToStream(OutputStream* stream)
{
SIZE_T size=0;
StringWriter writer(stream);
UINT pos=0;
for(auto it=First(); it->HasCurrent(); it->MoveNext())
	{
	if(pos>0)
		size+=writer.PrintChar('&');
	auto key=it->GetKey();
	auto value=it->GetValue();
	size+=writer.Print(key);
	size+=writer.PrintChar('=');
	size+=writer.Print(value);
	pos++;
	}
return size;
}

}}