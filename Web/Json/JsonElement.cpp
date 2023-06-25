//=================
// JsonElement.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringReader.h"
#include "Storage/Streams/StringWriter.h"
#include "Storage/StaticBuffer.h"
#include "JsonElement.h"

using namespace Storage;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Json {


//==================
// Con-/Destructors
//==================

JsonElement::JsonElement()
{
Elements=new ElementMap();
}


//========
// Common
//========

Handle<JsonElement> JsonElement::FromStream(InputStream* stream)
{
if(!stream)
	return nullptr;
Handle<JsonElement> json=new JsonElement();
json->ReadFromStream(stream);
return json;
}

Handle<JsonElement> JsonElement::FromString(Handle<String> str)
{
if(!str)
	return nullptr;
Handle<StaticBuffer> buf=new StaticBuffer(str->Begin());
return FromStream(buf);
}

Handle<JsonList> JsonElement::GetList(Handle<String> key)
{
return Convert<JsonList>(Elements->Get(key));
}

Handle<String> JsonElement::GetString(Handle<String> key)
{
return Convert<String>(Elements->Get(key));
}

SIZE_T JsonElement::ReadFromStream(InputStream* stream)
{
SIZE_T size=0;
StringReader reader(stream);
while(1)
	{
	size+=reader.FindChar("\"}");
	if(reader.LastChar=='}')
		break;
	Handle<String> key=reader.ReadString(&size, "\"");
	size+=reader.FindChar("\"[-.0123456789nft}");
	if(reader.LastChar=='\"')
		{
		Handle<String> value=reader.ReadString(&size, "\"");
		Elements->Set(key, value);
		continue;
		}
	if(reader.LastChar=='[')
		{
		Handle<JsonList> list=new JsonList();
		while(1)
			{
			size+=reader.FindChar("\"{]");
			if(reader.LastChar=='\"')
				{
				Handle<String> value=reader.ReadString(&size, "\"");
				list->Append(value);
				continue;
				}
			if(reader.LastChar=='{')
				{
				Handle<JsonElement> json=new JsonElement();
				size+=json->ReadFromStream(stream);
				list->Append(json);
				continue;
				}
			if(reader.LastChar==']')
				break;
			}
		Elements->Set(key, list);
		continue;
		}
	if(reader.LastChar=='}')
		break;
	TCHAR str[32];
	str[0]=reader.LastChar;
	UINT len=reader.ReadString(&str[1], 31, " ,\r\n}");
	size+=len;
	str[len+1]=0;
	Handle<String> value=new String(str);
	Elements->Set(key, value);
	if(reader.LastChar=='}')
		break;
	}
return size;
}

SIZE_T JsonElement::WriteToStream(OutputStream* stream, UINT level)
{
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("\r\n");
size+=writer.PrintChar('\t', level);
size+=writer.Print("{");
UINT pos=0;
for(auto it=Elements->First(); it->HasCurrent(); it->MoveNext())
	{
	if(pos++>0)
		size+=writer.Print(",");
	size+=writer.Print("\r\n");
	size+=writer.PrintChar('\t', level);
	auto key=it->GetKey();
	size+=writer.Print("\"");
	size+=writer.Print(key);
	size+=writer.Print("\": ");
	auto value=it->GetValue();
	auto str=Convert<String>(value);
	if(str)
		{
		size+=writer.Print("\"");
		size+=writer.Print(str);
		size+=writer.Print("\"");
		continue;
		}
	auto list=Convert<JsonList>(value);
	if(list)
		{
		UINT list_pos=0;
		size+=writer.Print("[");
		for(auto it_list=list->First(); it->HasCurrent(); it->MoveNext())
			{
			auto list_item=it_list->GetCurrent();
			auto list_str=Convert<String>(list_item);
			if(list_str)
				{
				if(list_pos>0)
					size+=writer.Print(", ");
				size+=writer.Print("\"");
				size+=writer.Print(list_str);
				size+=writer.Print("\"");
				continue;
				}
			auto list_json=Convert<JsonElement>(list_item);
			if(list_json)
				{
				if(list_pos>0)
					size+=writer.Print(",");
				size+=list_json->WriteToStream(stream, level+1);
				continue;
				}
			}
		}
	}
size+=writer.Print("\r\n");
size+=writer.PrintChar('\t', level);
size+=writer.Print("}");
return size;
}

}