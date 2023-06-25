//================
// WebDataRow.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StringWriter.h"
#include "WebGraph.h"
#include "WebDataRow.h"

using namespace Graphics;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {
		namespace Graphs {


//==================
// Con-/Destructors
//==================

WebDataRow::WebDataRow(WebGraph* graph, LPCSTR id, Handle<Sentence> name, COLOR c, Handle<ValueVector> values):
Color(c),
Id(id),
Name(name),
Values(values)
{
graph->Rows->Add(this);
}


//========
// Common
//========

SIZE_T WebDataRow::WriteToStream(OutputStream* stream, INT offset, UINT div, INT min, INT max)
{
div=MAX(div, 1);
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("[ ");
INT value_sum=0;
INT value_count=0;
UINT count=Values->GetCount();
for(UINT u=0; u<count; u++)
	{
	INT value=Values->GetAt(u);
	value+=offset;
	if((value>=min)&&(value<=max))
		{
		value_sum+=value;
		value_count++;
		}
	if((u%div)!=(div-1))
		continue;
	if(size>2)
		size+=writer.Print(", ");
	if(value_count==0)
		{
		value=max+1;
		}
	else
		{
		value=value_sum/value_count;
		}
	size+=writer.Print("%i", value);
	value_sum=0;
	value_count=0;
	}
size+=writer.Print(" ]");
return size;
}

}}}