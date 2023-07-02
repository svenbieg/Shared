//=============
// OtaUpdate.h
//=============

#pragma once


//=======
// Using
//=======

#include "Network/Http/HttpConnection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Ota {


//============
// OTA-Update
//============

class OtaUpdate: public Object
{
private:
	// Using
	using HttpConnection=Network::Http::HttpConnection;

public:
	// Con-/Destructors
	OtaUpdate();

	// Common
	VOID Abort();
	VOID Begin(Handle<String> Url);
	Event<OtaUpdate> Failed;
	Event<OtaUpdate> Successful;
	Event<OtaUpdate, Handle<String>> Status;

private:
	// Common
	VOID DoDownload(Handle<String> Url);
	VOID DoFailure(Handle<String> Status);
	VOID DoStatus(Handle<String> Status);
	VOID DoSuccess(Handle<String> Status);
	VOID DoUpdate(Handle<String> Url);
	Signal cDone;
	Mutex cMutex;
	Handle<HttpConnection> hConnection;
};

}}