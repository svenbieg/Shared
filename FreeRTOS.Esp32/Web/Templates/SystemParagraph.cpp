//=====================
// SystemParagraph.cpp
//=====================

#include "pch.h"


//=======
// Using
//=======

#include "Devices/MemoryClass.h"
#include "Html/Elements/HtmlBreak.h"
#include "Html/Elements/HtmlCaption.h"
#include "Html/Elements/HtmlLabel.h"
#include "Html/Elements/HtmlText.h"
#include "IoT/Application.h"
#include "Web/Elements/Tables/WebTable.h"
#include "Web/Elements/WebButton.h"
#include "Web/Elements/WebGrid.h"
#include "Web/Elements/WebInput.h"
#include "Web/Elements/WebLabel.h"
#include "Web/Elements/WebLog.h"
#include "System/System.h"
#include "SystemParagraph.h"

using namespace Devices;
using namespace Html::Elements;
using namespace Html::Elements::Tables;
using namespace IoT;
using namespace Web::Elements;
using namespace Web::Elements::Tables;


//===========
// Namespace
//===========

namespace Web {
	namespace Templates {


//=======
// Using
//=======

using System=::System::System;


//=========
// Strings
//=========

LPCSTR strSystem="System";


//==================
// Con-/Destructors
//==================

SystemParagraph::SystemParagraph(HtmlNode* parent):
WebParagraph(parent, strSystem)
{
auto app=Application::Current;
LPCSTR str_ver="Version";
LPCSTR str_system_start="System-Start";
LPCSTR str_mem="\1de:Arbeitsspeicher\0en:Memory\0";
auto table=new WebTable(this);
	{
	table->AddColumn();
	table->AddColumn("min-width:180px");
	table->AddRow(str_ver, app->Version);
	table->AddRow(str_system_start, System::Start, "systemParagraphSystemStart");
	auto row=new HtmlRow(table);
		{
		auto cell=new HtmlCell(row, HtmlCellType::Header); new HtmlText(cell, str_mem);
		cell=new HtmlCell(row);
			{
			auto memory=Memory::Get();
			new WebLabel(cell, memory->Available, "systemParagraphMemoryAvailable");
			new HtmlText(cell, " / ");
			new WebLabel(cell, memory->Total, "systemParagraphMemoryTotal");
			}
		}
	}
LPCSTR str_reload="setTimeout(function() { location.reload(); }, 1000);";
LPCSTR str_reset="\1de:Zurücksetzen\0en:Reset\0";
LPCSTR str_restart="\1de:Neustart\0en:Restart\0";
LPCSTR str_update="Update";
auto grid=new WebGrid(this);
	{
	auto row=new HtmlRow(grid);
	auto btn=grid->AddButton("systemParagraphResetButton", str_reset);
		{
		btn->Clicked.Add(&System::Reset);
		btn->Script=str_reload;
		}
	btn=grid->AddButton("systemParagraphRestartButton", str_restart);
		{
		btn->Clicked.Add(&System::Restart);
		btn->Script=str_reload;
		}
	btn=grid->AddButton("systemParagraphUpdateButton", str_update);
		{
		btn->Clicked.Add(app, &Application::Update);
		}
	auto cell=new HtmlCell(row);
		{
		new WebLabel(cell, app->UpdateStatus, "systemParagraphUpdateStatus");
		}
	}
LPCSTR str_protocol="\1de:Protokoll\0en:Protocol\0";
auto protocol=new WebParagraph(parent, str_protocol);
auto log=new WebLog(protocol, "systemParagraphLogBox", app->Log);
log->Style="font-size:smaller";
}

}}