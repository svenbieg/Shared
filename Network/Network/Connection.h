//==============
// Connection.h
//==============

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "IpAddress.h"


//===========
// Namespace
//===========

namespace Network {


//============
// Connection
//============

class Connection: public Object
{
public:
	// Using
	using ConnectionMap=Collections::Map<Handle<String>, Connection*>;

	// Common
	virtual VOID Connect()=0;
	Event<Connection> Connected;
	static Handle<ConnectionMap> Connections;
	static Connection* Current;
	virtual VOID Disconnect()=0;
	Event<Connection> Disconnected;
	Handle<String> HostName;
	Handle<String> Id;
	virtual BOOL IsConnected()=0;
	Handle<IpAddress> StationIp;
	Handle<IpAddress> StationGateway;
	Handle<IpAddress> StationSubnet;

protected:
	// Con-/Destructors
	Connection(Handle<String> Id);
	~Connection();

	Handle<String> hCmdConnect;
	Handle<String> hCmdDisconnect;
};

}