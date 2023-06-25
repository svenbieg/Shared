//==================
// WebDirectory.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Network/Connection.h"
#include "Storage/Streams/StringWriter.h"
#include "Storage/File.h"
#include "Storage/FileSize.h"
#include "WebDirectory.h"

using namespace Storage;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {


//=========
// Scripts
//=========

LPCSTR webDirectoryScript=
"const chunk_size=1024*1024;\r\n\r\n"
"function sendChunk(file, start)\r\n"
"{\r\n"
"var name=encodeURIComponent(file.name);\r\n"
"var end=start+chunk_size;\r\n"
"if(end>file.size)\r\n"
"\tend=file.size;\r\n"
"var progress=document.getElementById('UploadProgress');\r\n"
"var request=new XMLHttpRequest();\r\n"
"request.open('POST', '?name='.concat(name));\r\n"
"request.setRequestHeader('Content-Range', start+'-'+end+'/'+file.size);\r\n"
"request.onload=function(e)\r\n"
"\t{\r\n"
"\tif(request.status!=200)\r\n"
"\t\tend=file.size+1\r\n"
"\tif(end>=file.size)\r\n"
"\t\t{\r\n"
"\t\tlocation.reload();\r\n"
"\t\treturn;\r\n"
"\t\t}\r\n"
"\tsendChunk(file, end);\r\n"
"\t}\r\n"
"request.upload.onprogress=function(e)\r\n"
"\t{\r\n"
"\tprogress.value=(start+e.loaded)*100/file.size\r\n"
"\t}\r\n"
"request.send(file.slice(start, end));\r\n"
"}\r\n\r\n"
"function onUploadInputChanged(e)\r\n"
"{\r\n"
"var file=e.target.files[0];\r\n"
"var sel=document.getElementById('UploadInput');"
"sel.value='';\r\n"
"var progress=document.getElementById('UploadProgress');\r\n"
"progress.style='visibility:visible';\r\n"
"sendChunk(file, 0)\r\n"
"}\r\n\r\n"
"function onDragOver(e)\r\n"
"{\r\n"
"e.stopPropagation();\r\n"
"e.preventDefault();\r\n"
"e.dataTransfer.dropEffect='copy';\r\n"
"}\r\n\r\n"
"document.addEventListener(\"DOMContentLoaded\", function ()\r\n"
"{\r\n"
"document.getElementById('UploadInput').addEventListener('change', onUploadInputChanged, false);\r\n"
"document.addEventListener('dragover', onDragOver, false);"
"document.addEventListener('drop', onUploadInputChanged, false);"
"});\r\n\r\n";


//==================
// Con-/Destructors
//==================

WebDirectory::WebDirectory(Handle<Directory> dir):
hDirectory(dir)
{}


//========
// Common
//========

SIZE_T WebDirectory::WriteToStream(OutputStream* stream, Handle<String> root)
{
SIZE_T size=0;
StringWriter writer(stream);
size+=writer.Print("<!DOCTYPE html>\r\n");
size+=writer.Print("<html>\r\n<head>\r\n<title>");
auto path=hDirectory->GetPath();
Handle<String> full_path=new String("%s/%s", root->Begin(), path->Begin());
size+=writer.Print(full_path);
size+=writer.Print("</title>\r\n");
size+=writer.Print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\r\n\r\n");
size+=writer.Print("<style type=\"text/css\">\r\n");
size+=writer.Print("a { color:blue; text-decoration:none; }\r\n");
size+=writer.Print("a:link { color:blue; }\r\n");
size+=writer.Print("a:visited { color:blue; }\r\n");
size+=writer.Print("td.name { padding-right:8px; text-align:left; }\r\n");
size+=writer.Print("td.size { text-align:right; }\r\n");
size+=writer.Print("th { text-align:left; }\r\n");
size+=writer.Print("</style>\r\n\r\n");
size+=writer.Print("<script language=\"javascript\" type=\"text/javascript\">\r\n\r\n");
size+=writer.Print(webDirectoryScript);
size+=writer.Print("</script>\r\n\r\n");
size+=writer.Print("</head>\r\n\r\n<body>\r\n\r\n<h1>");
size+=writer.Print(full_path);
size+=writer.Print("</h1>\r\n\r\n<p>\r\n<table>\r\n");
auto parent=PathGetDirectory(path->Begin());
if(parent)
	{
	size+=writer.Print("  <tr><th><a href=\"/");
	size+=writer.Print(parent);
	size+=writer.Print("\">..</a></th></tr>\r\n");
	}
else
	{
	size+=writer.Print("  <tr><th><a href=\"index.html\">..</a></th></tr>\r\n");
	}
for(auto it=hDirectory->First(); it->HasCurrent(); it->MoveNext())
	{
	auto item=it->GetCurrent();
	auto dir=Convert<Storage::Directory>(item);
	if(!dir)
		continue;
	size+=writer.Print("  <tr>");
	size+=writer.Print("<th><a href=\"");
	size+=writer.Print(dir->GetPath());
	size+=writer.Print("\">");
	size+=writer.Print(dir->GetName());
	size+=writer.Print("</a></th>");
	size+=writer.Print("</tr>\r\n");
	}
size+=writer.Print("</table>\r\n</p>\r\n\r\n");
size+=writer.Print("<p>\r\n<table>\r\n");
for(auto it=hDirectory->First(); it->HasCurrent(); it->MoveNext())
	{
	auto item=it->GetCurrent();
	if(Convert<Storage::Directory>(item))
		continue;
	auto file=Convert<File>(item);
	if(!file)
		continue;
	if(Failed(file->Create()))
		continue;
	size+=writer.Print("  <tr>");
	size+=writer.Print("<td class=\"name\"><a href=\"");
	size+=writer.Print(path);
	size+=writer.Print("/");
	auto name=file->GetName();
	size+=writer.Print(name);
	size+=writer.Print("\" download>");
	size+=writer.Print(name);
	size+=writer.Print("</a></td>");
	size+=writer.Print("<td class=\"size\">");
	auto file_size=file->GetSize();
	size+=writer.Print(FileSize::ToString(file_size));
	size+=writer.Print("</td>");
	size+=writer.Print("</tr>\r\n");
	}
size+=writer.Print("</table><br />\r\n");
size+=writer.Print("<input type=\"file\" id=\"UploadInput\" name=\"files[]\" style=\"display: none;\" /><br />");
size+=writer.Print("<input type=\"button\" value=\"Datei hinzufügen...\" onclick=\"document.getElementById('UploadInput').click();\" />");
size+=writer.Print("<br /><br />");
size+=writer.Print("<progress id=\"UploadProgress\" min=\"0\" max=\"100\" value=\"0\" style=\"visibility:hidden\" />");
size+=writer.Print("</p>\r\n");
size+=writer.Print("</body>\r\n</html>\r\n");
return size;
}

}