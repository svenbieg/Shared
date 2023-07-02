//======================
// ShellCommandList.cpp
//======================

#include "pch.h"


//=======
// Using
//=======

#include "Shell.h"
#include "ShellCommandList.h"
#include "Variable.h"


//===========
// Namespace
//===========

namespace Runtime {


//==================
// Con-/Destructors
//==================

ShellCommandList::ShellCommandList()
{
hCurrent=this;
Add("echo", [](Shell* shell)
	{
	if(!shell)
		return;
	shell->Print("echo\r\n");
	});
Add("globals", [](Shell* shell)
	{
	if(!shell)
		return;
	for(auto it=Globals->First(); it->HasCurrent(); it->MoveNext())
		{
		auto var=it->GetValue();
		auto name=var->Name;
		auto value=var->ToString();
		LPCTSTR pvalue=value? value->Begin(): nullptr;
		shell->Print("%s: %s\r\n", name->Begin(), pvalue);
		}
	});
}


//========
// Common
//========

Handle<ShellCommandList> ShellCommandList::Get()
{
if(!hCurrent)
	new ShellCommandList();
return hCurrent;
}


//================
// Common Private
//================

Handle<ShellCommandList> ShellCommandList::hCurrent;

}