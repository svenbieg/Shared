//=============
// WebSite.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Filesystem/Directory.h"
#include "WebSite.h"

using namespace Storage;


//===========
// Namespace
//===========

namespace Web {


//==================
// Con-/Destructors
//==================

WebSite::WebSite(Handle<String> host_name)
{
Current=this;
Accounts=new WebAccountMap();
Public=new Workspace("Public");
auto public_dir=Filesystem::Directory::Open("Public");
Public->AddDirectory(public_dir);
if(host_name)
	{
	Protected=new Workspace("Protected");
	Protected->AddDirectory(Public);
	auto protected_dir=Filesystem::Directory::Open("Protected");
	Protected->AddDirectory(protected_dir);
	}
hWebServer=new WebServer(this, host_name);
hWebServer->Listen();
}


//========
// Common
//========

Handle<WebSite> WebSite::Current;

}