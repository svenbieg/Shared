//================
// WebDirectory.h
//================

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/OutputStream.h"
#include "Storage/Directory.h"
#include "WebPage.h"


//===========
// Namespace
//===========

namespace Web {


//===============
// Web-Directory
//===============

class WebDirectory: public WebPage
{
private:
	// Using
	using Directory=Storage::Directory;
	using OutputStream=Storage::Streams::OutputStream;

public:
	// Con-/Destructors
	WebDirectory(Handle<Directory> Directory);

	// Common
	SIZE_T WriteToStream(OutputStream* Stream, Handle<String> Root);

private:
	// Common
	Handle<Directory> hDirectory;
};

}