//==================
// WiFiConnection.h
//==================

#pragma once


//=======
// Using
//=======

#include "Network/Dns/DnsServer.h"
#include "Network/Connection.h"
#include "Core/Timer.h"
#include "StringVariable.h"
#include "WiFiEvent.h"


//===========
// Namespace
//===========

namespace Network {
	namespace WiFi {


//========
// Status
//========

enum class WiFiConnectionStatus: UINT
{
Disconnected,
Connecting,
Connected,
Offline
};


//=================
// WiFi-Connection
//=================

class WiFiConnection: public Connection
{
private:
	// Using
	using DnsServer=Network::Dns::DnsServer;
	using IpAddress=Network::IpAddress;
	using Timer=Core::Timer;

public:
	// Con-/Destructors
	WiFiConnection();

	// Common
	Handle<IpAddress> AccessPointIp;
	Handle<String> AccessPointNetwork;
	Handle<String> AccessPointPassword;
	Handle<IpAddress> AccessPointSubnet;
	static BYTE Channel;
	VOID Close();
	VOID Connect()override;
	static Handle<WiFiConnection> Current;
	VOID Disconnect()override;
	BOOL IsConnected()override { return StationIp->Get()!=0; }
	VOID Notify(WiFiEvent Event, WiFiEventArgs* Args);
	Handle<StringVariable> StationNetwork;
	Handle<StringVariable> StationPassword;

private:
	// Common
	VOID DoDisconnect();
	VOID DoUpdate();
	VOID OnTimerTriggered();
	Handle<String> hAccessPointNetwork;
	Handle<DnsServer> hDnsServer;
	Handle<Timer> hTimer;
	UINT uStationGateway;
	UINT uStationIp;
	UINT uStationSubnet;
	WiFiConnectionStatus uStatus;
};

}}