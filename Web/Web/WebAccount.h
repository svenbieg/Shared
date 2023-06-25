//==============
// WebAccount.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Workspace.h"


//===========
// Namespace
//===========

namespace Web {


//======================
// Forward-Declarations
//======================

class WebSite;


//=============
// Web-Account
//=============

class WebAccount: public Object
{
public:
	// Using
	using Workspace=Storage::Workspace;

	// Con-/Destructors
	WebAccount(WebSite* WebSite, Handle<String> Email, Handle<String> Name);

	// Common
	Handle<Workspace> DocumentRoot;
	Handle<String> const Email;
	Handle<String> const Name;
};

}