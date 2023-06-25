//==============
// WebGraph.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "Storage/Streams/StringWriter.h"
#include "WebGraph.h"

using namespace Culture;
using namespace Graphics;
using namespace Html;
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

WebGraph::WebGraph(HtmlNode* parent, Handle<String> id):
HtmlNode(parent, "canvas", id),
Divisor(1),
GridColor(Colors::LightGray),
Offset(0)
{
AxisX=new WebAxis();
AxisY=new WebAxis();
Rows=new RowList();
Document->AddScript(this, &WebGraph::WriteScriptToStream);
}


//========
// Common
//========

VOID WebGraph::AddRow(LPCSTR id, Handle<Sentence> name, COLOR c, Handle<ValueVector> values)
{
new WebDataRow(this, id, name, c, values);
}


//================
// Common Private
//================

SIZE_T WebGraph::WriteScriptToStream(OutputStream* stream, WebContext* context)
{
SIZE_T size=0;
StringWriter writer(stream);
auto lng=context->Language;
size+=writer.Print("\r\nfunction draw_");
size+=writer.Print(Id);
size+=writer.Print("()\r\n{\r\n");
UINT axis_x_count=AxisX->Points->GetCount();
INT min_x=0;
INT max_x=0;
if(axis_x_count>0)
	{
	size+=writer.Print("var axisX=[ ");
	UINT pos=0;
	for(auto it=AxisX->Points->First(); it->HasCurrent(); it->MoveNext())
		{
		auto x=it->GetKey();
		auto label=it->GetValue();
		if(pos++>0)
			size+=writer.Print(", ");
		size+=writer.Print("[ ");
		size+=writer.Print("%i", x);
		size+=writer.Print(", '");
		size+=writer.Print(label->Begin(lng));
		size+=writer.Print("' ]");
		min_x=MIN(min_x, x);
		max_x=MAX(max_x, x);
		}
	size+=writer.Print("];\r\n");
	}
UINT axis_y_count=AxisY->Points->GetCount();
INT min_y=0;
INT max_y=0;
if(axis_y_count>0)
	{
	size+=writer.Print("var axisY=[ ");
	UINT pos=0;
	for(auto it=AxisY->Points->First(); it->HasCurrent(); it->MoveNext())
		{
		auto y=it->GetKey();
		auto label=it->GetValue();
		if(pos++>0)
			size+=writer.Print(", ");
		size+=writer.Print("[ ");
		size+=writer.Print("%i", y);
		size+=writer.Print(", '");
		size+=writer.Print(label->Begin(lng));
		size+=writer.Print("' ]");
		min_y=MIN(min_y, y);
		max_y=MAX(max_y, y);
		}
	size+=writer.Print("];\r\n");
	}
UINT row_count=Rows->GetCount();
if(row_count>0)
	{
	for(auto it=Rows->First(); it->HasCurrent(); it->MoveNext())
		{
		auto row=it->GetCurrent();
		size+=writer.Print("var ");
		size+=writer.Print(row->Id);
		size+=writer.Print("=");
		size+=row->WriteToStream(stream, Divisor, min_y, max_y, Offset);
		size+=writer.Print(";\r\n");
		}
	size+=writer.Print("var rows=[\r\n\t");
	UINT pos=0;
	for(auto it=Rows->First(); it->HasCurrent(); it->MoveNext())
		{
		auto row=it->GetCurrent();
		if(pos++>0)
			size+=writer.Print(",\r\n\t");
		size+=writer.Print("[ '");
		size+=writer.Print(row->Name->Begin(lng));
		size+=writer.Print("', '");
		size+=writer.Print(row->Color.ToString());
		size+=writer.Print("', ");
		size+=writer.Print(row->Id);
		size+=writer.Print(" ]");
		}
	size+=writer.Print("];\r\n");
	}
size+=writer.Print("var row_count=%u;\r\n", row_count);
size+=writer.Print("var canvas=document.getElementById('%s');\r\n", Id->Begin());
size+=writer.Print("var scale=window.devicePixelRatio;\r\n");
size+=writer.Print("var style=window.getComputedStyle(canvas, null);\r\n");
size+=writer.Print("var font_family=style.getPropertyValue('font-family');\r\n");
size+=writer.Print("var font_size=parseInt(style.getPropertyValue('font-size'))*scale;\r\n");
size+=writer.Print("var font_color=style.getPropertyValue('color');\r\n");
size+=writer.Print("canvas.width=800*scale;\r\n");
size+=writer.Print("canvas.height=canvas.width*3/4;\r\n");
size+=writer.Print("var width=canvas.width-1;\r\n");
size+=writer.Print("var height=canvas.height-1;\r\n");
size+=writer.Print("var left=0;\r\n");
size+=writer.Print("var top=0;\r\n");
size+=writer.Print("var min_x=%i;\r\n", min_x);
size+=writer.Print("var max_x=%i;\r\n", max_x);
size+=writer.Print("var div=%i;\r\n", Divisor);
size+=writer.Print("var min_y=%i;\r\n", min_y);
size+=writer.Print("var max_y=%i;\r\n", max_y);
size+=writer.Print("var margin_x=8;\r\n");
size+=writer.Print("var margin_y=8;\r\n");
auto grid_color=GridColor.ToString();
size+=writer.Print("var grid_color='%s';\r\n", grid_color->Begin());
size+=writer.Print("var context=canvas.getContext('2d');\r\n");
size+=writer.Print("context.clearRect(0, 0, width, height);\r\n");
size+=writer.Print("context.font=font_size.toString()+\"px \"+font_family;\r\n");
if(row_count>0)
	{
	size+=writer.Print("var max_name_width=0;\r\n");
	size+=writer.Print("rows.forEach(function(row) {\r\n");
	size+=writer.Print("\tvar name=row[0];\r\n");
	size+=writer.Print("\tvar tm=context.measureText(name);\r\n");
	size+=writer.Print("\tif(tm.width>max_name_width)\r\n");
	size+=writer.Print("\t\tmax_name_width=tm.width\r\n");
	size+=writer.Print("\t});\r\n");
	size+=writer.Print("width-=font_size+margin_x+max_name_width;\r\n");
	size+=writer.Print("var urow=0;\r\n");
	size+=writer.Print("var y=top+(height-row_count*font_size-(row_count-1)*margin_y)/2;\r\n");
	size+=writer.Print("rows.forEach(function(row) {\r\n");
	size+=writer.Print("\tvar name=row[0];");
	size+=writer.Print("\tvar color=row[1];");
	size+=writer.Print("\tcontext.fillStyle=color;\r\n");
	size+=writer.Print("\tcontext.fillRect(width, y, font_size, font_size);\r\n");
	size+=writer.Print("\tcontext.fillStyle=font_color;\r\n");
	size+=writer.Print("\tcontext.fillText(name, width+font_size+margin_x, y+font_size-font_size/8);\r\n");
	size+=writer.Print("\ty+=font_size+margin_y\r\n");
	size+=writer.Print("\t});\r\n");
	}
size+=writer.Print("context.fillStyle=font_color;\r\n");
size+=writer.Print("context.strokeStyle=grid_color;\r\n");
if(AxisX->Name)
	{
	size+=writer.Print("var name_x='\r\n");
	size+=writer.Print(AxisX->Name->Begin(lng));
	if(AxisX->Unit)
		{
		size+=writer.Print("/");
		size+=writer.Print(AxisX->Unit->Begin(lng));
		}
	size+=writer.Print("';\r\n");
	size+=writer.Print("var name_x_tm=context.measureText(name_x);\r\n");
	size+=writer.Print("width-=margin_x+name_x_tm.width;\r\n");
	size+=writer.Print("context.fillText(name_x, width+margin_x, height);\r\n");
	}
if(AxisY->Name)
	{
	size+=writer.Print("var name_y='");
	size+=writer.Print(AxisY->Name->Begin(lng));
	if(AxisY->Unit)
		{
		size+=writer.Print("/");
		size+=writer.Print(AxisY->Unit->Begin(lng));
		}
	size+=writer.Print("';\r\n");
	size+=writer.Print("var name_y_tm=context.measureText(name_y);\r\n");
	size+=writer.Print("left+=name_y_tm.width+margin_x;\r\n");
	size+=writer.Print("width-=name_y_tm.width+margin_x;\r\n");
	size+=writer.Print("context.fillText(name_y, 0, font_size);\r\n");
	}
if(axis_x_count>0)
	{
	size+=writer.Print("var pt=axisX[axisX.length-1];\r\n");
	size+=writer.Print("var tm=context.measureText(pt[1]);");
	size+=writer.Print("width-=tm.width/2;\r\n");
	size+=writer.Print("height-=font_size+margin_y;\r\n");
	}
if(axis_y_count>0)
	{
	size+=writer.Print("var max_text_width=0;\r\n");
	size+=writer.Print("axisY.forEach(function(pt) {\r\n");
	size+=writer.Print("\tvar tm=context.measureText(pt[1]);\r\n");
	size+=writer.Print("\tif(tm.width>max_text_width)\r\n");
	size+=writer.Print("\t\tmax_text_width=tm.width;\r\n");
	size+=writer.Print("\t});\r\n");
	size+=writer.Print("width-=max_text_width+margin_x;\r\n");
	size+=writer.Print("height-=font_size/2;\r\n");
	size+=writer.Print("left+=max_text_width+margin_x;\r\n");
	size+=writer.Print("top+=font_size/2;\r\n");
	}
if(axis_x_count>0)
	{
	size+=writer.Print("context.beginPath();\r\n");
	size+=writer.Print("axisX.forEach(function(pt) {\r\n");
	size+=writer.Print("\tvar x=left+pt[0]/(max_x-min_x)*width;\r\n");
	size+=writer.Print("\tcontext.moveTo(x, top);\r\n");
	size+=writer.Print("\tcontext.lineTo(x, top+height);\r\n");
	size+=writer.Print("\tvar tm=context.measureText(pt[1]);");
	size+=writer.Print("\tcontext.fillText(pt[1], x-tm.width/2, top+height+font_size+margin_y);\r\n");
	size+=writer.Print("\t});\r\n");
	size+=writer.Print("context.stroke();\r\n");
	}
if(axis_y_count>0)
	{
	size+=writer.Print("context.beginPath();\r\n");
	size+=writer.Print("axisY.forEach(function(pt) {\r\n");
	size+=writer.Print("\tvar y=top+height-(pt[0]-min_y)/(max_y-min_y)*height;\r\n");
	size+=writer.Print("\tcontext.moveTo(left, y);\r\n");
	size+=writer.Print("\tcontext.lineTo(left+width, y);\r\n");
	size+=writer.Print("\tvar tm=context.measureText(pt[1]);");
	size+=writer.Print("\tcontext.fillText(pt[1], left-tm.width-margin_x, y+font_size/2);\r\n");
	size+=writer.Print("\t});\r\n");
	size+=writer.Print("context.stroke();\r\n");
	}
size+=writer.Print("rows.forEach(function(row) {\r\n");
size+=writer.Print("\tvar name=row[0];\r\n");
size+=writer.Print("\tvar color=row[1];\r\n");
size+=writer.Print("\tvar values=row[2];\r\n");
size+=writer.Print("\tcontext.fillStyle=color;\r\n");
size+=writer.Print("\tcontext.strokeStyle=color;\r\n");
size+=writer.Print("\tcontext.beginPath();\r\n");
size+=writer.Print("\tvar was_outside=true;\r\n");
size+=writer.Print("\tvar pos=0;\r\n");
size+=writer.Print("\tvalues.forEach(function(value) {\r\n");
size+=writer.Print("\t\tvar x=left+pos*div/(max_x-min_x)*width;\r\n");
size+=writer.Print("\t\tvar y=top+height-(value-min_y)/(max_y-min_y)*height;\r\n");
size+=writer.Print("\t\tvar outside=(value<min_y||value>max_y);\r\n");
size+=writer.Print("\t\tif(was_outside||outside)\r\n");
size+=writer.Print("\t\t\t{\r\n");
size+=writer.Print("\t\t\tif(!outside){ context.fillRect(x, y, 1, 1); }\r\n");
size+=writer.Print("\t\t\tcontext.moveTo(x, y);\r\n");
size+=writer.Print("\t\t\t}\r\n");
size+=writer.Print("\t\telse { context.lineTo(x, y); }\r\n");
size+=writer.Print("\t\twas_outside=outside;\r\n");
size+=writer.Print("\t\tpos++;\r\n");
size+=writer.Print("\t\t});\r\n");
size+=writer.Print("\tcontext.stroke();\r\n");
size+=writer.Print("\t});\r\n");
size+=writer.Print("}\r\n");
size+=writer.Print("window.addEventListener(\"DOMContentLoaded\", function(e) { draw_");
size+=writer.Print(Id->Begin());
size+=writer.Print("(); });\r\n\r\n");
return size;
}

}}}