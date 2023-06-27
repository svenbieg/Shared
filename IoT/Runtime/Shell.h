//=========
// Shell.h
//=========

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"


//===========
// Namespace
//===========

namespace Runtime {


//==========
// Settings
//==========

constexpr INT SHELL_CMD_MAX=128;


//=======
// Shell
//=======

class Shell: public Object
{
public:
	// Using
	using RandomAccessStream=Storage::Streams::RandomAccessStream;

	// Con-/Destructors
	Shell(Handle<RandomAccessStream> Stream);

	// Common
	VOID Print(LPCSTR Text);
	VOID Print(Handle<String> Text);
	template <class... _args_t> VOID Print(LPCSTR Format, _args_t... Arguments) { Print(new String(Format, Arguments...)); }
	VOID Process(Handle<String> Command);
	static VOID Process(Shell* Shell, Handle<String> Command);

private:
	// Common
	Handle<RandomAccessStream> hStream;
	INT iLength;
	TCHAR pCommand[SHELL_CMD_MAX];
};

}