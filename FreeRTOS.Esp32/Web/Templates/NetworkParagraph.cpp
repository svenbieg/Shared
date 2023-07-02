//======================
// NetworkParagraph.cpp
//======================

#include "pch.h"


//=======
// Using
//=======

#include "Network/WiFi/WiFiConnection.h"
#include "Html/Elements/HtmlCaption.h"
#include "Html/Elements/HtmlLabel.h"
#include "Web/Elements/Tables/WebTable.h"
#include "Web/Elements/WebGrid.h"
#include "Web/Elements/WebInput.h"
#include "NetworkParagraph.h"

using namespace Html::Elements;
using namespace Network::WiFi;
using namespace Web::Elements;
using namespace Web::Elements::Tables;


//===========
// Namespace
//===========

namespace Web {
	namespace Templates {


//=========
// Strings
//=========

LPCSTR strNetwork="\1de:Netzwerk\0en:Network\0";


//==================
// Con-/Destructors
//==================

NetworkParagraph::NetworkParagraph(HtmlNode* parent):
WebParagraph(parent, strNetwork)
{
auto con=WiFiConnection::Current;
LPCSTR str_ip="\1de:Ip-Adresse\0en:Ip-Address\0";
LPCSTR str_gateway="Gateway";
LPCSTR str_subnet="\1de:Subnetz\0en:Subnet\0";
auto table=new WebTable(this);
	{
	table->AddColumn();
	table->AddColumn("min-width:150px");
	table->AddRow(str_ip, con->StationIp, "networkParagraphStationIp");
	table->AddRow(str_gateway, con->StationGateway, "networkParagraphGateway");
	table->AddRow(str_subnet, con->StationSubnet, "networkParagraphSubnet");
	}
LPCSTR str_ssid="SSID";
auto label=new HtmlLabel(this, str_ssid);
	{
	new WebInput(label, con->StationNetwork, "networkParagraphStationSsidInput");
	label->Break();
	}
LPCSTR str_password="\1de:Passwort\0en:Password\0";
label=new HtmlLabel(this, str_password);
	{
	new WebInput(label, con->StationPassword, "networkParagraphStationPasswordInput", WebInputType::Password);
	label->Break();
	}
LPCSTR str_connect="\1de:Verbinden\0en:Connect\0";
auto grid=new WebGrid(this);
	{
	grid->AddButton("networkParagraphConnectButton", str_connect)->Clicked.Add(WiFiConnection::Current, &WiFiConnection::Connect);
	}
}

}}