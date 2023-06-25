//================
// Connection.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Connection.h"


//===========
// Namespace
//===========

namespace Network {


//========
// Common
//========

Handle<Connection::ConnectionMap> Connection::Connections;

Connection* Connection::Current=nullptr;


//============================
// Con-/Destructors Protected
//============================

Connection::Connection(Handle<String> id):
Id(id)
{
Current=this;
if(!Connections)
	Connections=new ConnectionMap();
Connections->Add(Id, this);
StationIp=new IpAddress("NetworkStationIp");
StationGateway=new IpAddress("NetworkStationGateway");
StationSubnet=new IpAddress("NetworkStationSubnet", 255, 255, 255, 0);
}

Connection::~Connection()
{
if(Current==this)
	Current=nullptr;
Connections->Remove(Id);
if(Connections->GetCount()==0)
	Connections=nullptr;
}

}