//=======
// Url.h
//=======

#pragma once


//=====
// URL
//=====

class Url
{
public:
	// Common
	static Handle<String> Decode(Handle<String> Url);
	static UINT Decode(LPTSTR Buffer, UINT Size, LPCTSTR Url, BOOL* Escape=nullptr);
};
