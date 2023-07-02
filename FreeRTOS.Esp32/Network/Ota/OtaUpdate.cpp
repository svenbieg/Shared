//===============
// OtaUpdate.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <esp_app_desc.h>
#include <esp_image_format.h>
#include <esp_ota_ops.h>
#include "Core/Application.h"
#include "Network/Http/HttpClient.h"
#include "Storage/Buffer.h"
#include "OtaUpdate.h"

using namespace Core;
using namespace Network::Http;
using namespace Storage;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Ota {


//=========
// Strings
//=========

LPCSTR strConnected="\1de:Verbunden\0en:Connected\0";
LPCSTR strConnecting="\1de:Verbinden...\0en:Connecting...\0";
LPCSTR strConnectionFailed="\1de:Verbindung fehlgeschlagen\0en:Connection failed\0";
LPCSTR strDownloadFailed="\1de:Download fehlgeschlagen\0en:Download failed\0";
LPCSTR strLatest="\1de:Aktuell\0en:Latest\0";
LPCSTR strSuccess="\1de:Erfolgreich\0en:Successful\0";


//==================
// Con-/Destructors
//==================

OtaUpdate::OtaUpdate()
{}


//========
// Common
//========

VOID OtaUpdate::Abort()
{
ScopedLock lock(cMutex);
if(!hConnection)
	return;
auto sock=hConnection->Socket;
sock->Close();
cDone.Wait(lock);
}

VOID OtaUpdate::Begin(Handle<String> url)
{
Abort();
ScopedLock lock(cMutex);
CreateTask(this, &OtaUpdate::DoUpdate, url);
}


//================
// Common Private
//================

VOID OtaUpdate::DoDownload(Handle<String> url)
{
auto app=Application::Current;
Handle<String> status;
try
	{
	status=strConnected;
	app->Dispatch(this, &OtaUpdate::DoStatus, status);
	Handle<HttpRequest> request=HttpRequest::FromUrl(url);
	hConnection->Send(request);
	auto response=hConnection->GetResponse();
	if(response->Status!=HttpStatus::Ok)
		{
		status=new String("%u - %s", (UINT)response->Status, HttpStatusToString(response->Status));
		app->Dispatch(this, &OtaUpdate::DoFailure, status);
		return;
		}
	UINT content_len=0;
	auto str_len=response->Properties->Get("Content-Length");
	if(str_len)
		str_len->Scan("%u", &content_len);
	if(!content_len)
		throw std::exception();
	Handle<Buffer> buf=new Buffer(PAGE_SIZE);
	auto pbuf=buf->Begin();
	UINT copy=sizeof(esp_image_header_t)+sizeof(esp_image_segment_header_t)+sizeof(esp_app_desc_t);
	if(content_len<copy)
		throw std::exception();
	SIZE_T read=hConnection->Read(pbuf, copy);
	auto pheader=pbuf;
	pheader+=sizeof(esp_image_header_t);
	pheader+=sizeof(esp_image_segment_header_t);
	auto app_new=(esp_app_desc_t const*)pheader;
	auto app_cur=esp_ota_get_app_description();
	if(StringCompare(app_new->version, app_cur->version)==0)
		{
		status=strLatest;
		app->Dispatch(this, &OtaUpdate::DoSuccess, status);
		return;
		}
	auto part=esp_ota_get_next_update_partition(NULL);
	if(!part)
		{
		DebugPrint("esp_ota_get_next_update_partition() failed\n");
		throw std::exception();
		}
	esp_ota_handle_t ota;
	if(esp_ota_begin(part, content_len, &ota)!=ESP_OK)
		{
		DebugPrint("esp_ota_begin() failed\n");
		throw std::exception();
		}
	UINT pos=0;
	while(pos<content_len)
		{
		if(esp_ota_write(ota, pbuf, read)!=ESP_OK)
			{
			DebugPrint("esp_ota_write() failed\n");
			throw std::exception();
			}
		pos+=read;
		INT progress=pos*100/content_len;
		status=new String("%i%%", progress);
		app->Dispatch(this, &OtaUpdate::DoStatus, status);
		if(pos==content_len)
			break;
		copy=MIN(content_len-pos, PAGE_SIZE);
		read=hConnection->Read(pbuf, copy);
		}
	if(esp_ota_end(ota)!=ESP_OK)
		{
		DebugPrint("esp_ota_end() failed\n");
		throw std::exception();
		}
	if(esp_ota_set_boot_partition(part)!=ESP_OK)
		{
		DebugPrint("esp_ota_set_boot_partition() failed\n");
		throw std::exception();
		}
	status=strSuccess;
	app->Dispatch(this, &OtaUpdate::DoSuccess, status);
	}
catch(std::exception const&)
	{
	status=strDownloadFailed;
	app->Dispatch(this, &OtaUpdate::DoFailure, status);
	}
}

VOID OtaUpdate::DoFailure(Handle<String> status)
{
if(status)
	Status(this, status);
Failed(this);
}

VOID OtaUpdate::DoStatus(Handle<String> status)
{
Status(this, status);
}

VOID OtaUpdate::DoSuccess(Handle<String> status)
{
if(status)
	Status(this, status);
Successful(this);
}

VOID OtaUpdate::DoUpdate(Handle<String> url)
{
UINT host_len=0;
StringFind(url->Begin(), "/", &host_len);
Handle<String> host=new String(host_len, url->Begin());
ScopedLock lock(cMutex);
auto app=Application::Current;
Handle<String> status=strConnected;
app->Dispatch(this, &OtaUpdate::DoStatus, status);
hConnection=HttpClient::Connect(host);
if(!hConnection)
	{
	status=strConnectionFailed;
	app->Dispatch(this, &OtaUpdate::DoFailure, status);
	return;
	}
lock.Unlock();
DoDownload(url);
lock.Lock();
hConnection=nullptr;
cDone.Broadcast();
}

}}