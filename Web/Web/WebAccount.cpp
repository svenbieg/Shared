//================
// WebAccount.cpp
//================

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

WebAccount::WebAccount(WebSite* web_site, Handle<String> email, Handle<String> name):
Email(email),
Name(name)
{
DocumentRoot=new Workspace("Private");
DocumentRoot->AddDirectory(web_site->Protected);
auto private_dir=Filesystem::Directory::Open("Private");
DocumentRoot->AddDirectory(private_dir);
web_site->Accounts->Set(Email, this);
}

}