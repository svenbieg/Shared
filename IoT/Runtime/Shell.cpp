//===========
// Shell.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Core/Application.h"
#include "Storage/Streams/StringReader.h"
#include "Storage/Streams/StringWriter.h"
#include "Shell.h"
#include "ShellCommandList.h"
#include "StringVariable.h"

using namespace Core;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Runtime {


//==================
// Con-/Destructors
//==================

Shell::Shell(Handle<RandomAccessStream> stream):
hStream(stream),
iLength(0),
pCommand()
{}


//========
// Common
//========

VOID Shell::Print(LPCSTR text)
{
if(!hStream)
	return;
StringWriter writer(hStream);
writer.Print(text);
hStream->Flush();
}

VOID Shell::Print(Handle<String> text)
{
if(!hStream)
	return;
StringWriter writer(hStream);
writer.Print(text);
hStream->Flush();
}

VOID Shell::Process(Handle<String> cmd)
{
Process(this, cmd);
}

VOID Shell::Process(Shell* shell, Handle<String> cmd)
{
if(!cmd)
	return;
auto cmds=ShellCommandList::Get();
std::function<VOID(Shell*)> proc;
if(cmds->TryGet(cmd, &proc))
	{
	proc(shell);
	return;
	}
CHAR key[SHELL_CMD_MAX];
CHAR value[SHELL_CMD_MAX];
if(cmd->Scan("%s=%s", key, SHELL_CMD_MAX, value, SHELL_CMD_MAX)==2)
	{
	auto var=Globals->Get(key);
	if(var)
		{
		var->FromString(value);
		}
	else
		{
		var=new StringVariable(key, value);
		}
	if(shell)
		{
		auto value=var->ToString();
		LPCTSTR pvalue=value? value->Begin(): nullptr;
		shell->Print("%s: %s\r\n", key, pvalue);
		}
	}
}


//================
// Common Private
//================

/*VOID Shell::OnSerialPortDataReceived()
{
StreamReader reader(hSerialPort);
StreamWriter writer(hSerialPort);
while(hSerialPort->Available())
	{
	CHAR c=(CHAR)reader.ReadByte();
	if(c==0)
		continue;
	if(c=='\n')
		continue;
	if(c==0x7F)
		{
		if(iLength<=0)
			continue;
		iLength--;
		writer.WriteByte(0x7F);
		writer.WriteByte(' ');
		writer.WriteByte(0x7F);
		continue;
		}
	if(c=='\r')
		{
		if(iLength>0)
			{
			pCommand[iLength]=0;
			Handle<String> cmd=new String(pCommand);
			Application::Current->Dispatch([this, cmd]() { ProcessCommand(cmd); });
			}
		iLength=0;
		writer.WriteByte('\r');
		writer.WriteByte('\n');
		continue;
		}
	if(c<0x20||c>0x7E)
		continue;
	if(iLength+2>=SHELL_CMD_MAX)
		{
		iLength=-1;
		continue;
		}
	if(iLength<0)
		continue;
	pCommand[iLength++]=c;
	writer.WriteByte(c);
	}
hSerialPort->Flush();
}*/

}