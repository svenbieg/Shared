//=================
// FlashDevice.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <esp_attr.h>
#include <esp_partition.h>
#include "FlashDevice.h"

using namespace Storage;

#define SPI_FLASH_SEC_SIZE 4096


//===========
// Namespace
//===========

namespace Devices {
	namespace Storage {


//========
// Common
//========

VOID FlashDevice::Erase(UINT64 offset, UINT size)
{
if(offset>=uSize)
	return;
UINT pos=(UINT)offset;
UINT block_pos=pos%SPI_FLASH_SEC_SIZE;
pos-=block_pos;
size=BlockAlign(size, SPI_FLASH_SEC_SIZE);
UINT disk_pos=uOffset+uSize-pos-size;
if(esp_flash_erase_region(esp_flash_default_chip, disk_pos, size)!=ESP_OK)
	{
	DebugPrint("esp_flash_erase_region() failed\n");
	}
}

UINT FlashDevice::GetBlockSize()
{
return SPI_FLASH_SEC_SIZE;
}

Handle<FlashDevice> FlashDevice::Open()
{
if(!hCurrent)
	hCurrent=new FlashDevice();
return hCurrent;
}

SIZE_T FlashDevice::Read(FILE_SIZE offset, VOID* pbuf, SIZE_T size)
{
if(!pbuf||!size)
	return 0;
BYTE* pdst=(BYTE*)pbuf;
SIZE_T read=0;
while(read<size)
	{
	UINT disk_offset=(UINT)offset;
	UINT available=DiskOffset(&disk_offset);
	UINT copy=MIN(available, size-read);
	if(!copy)
		return read;
	if(esp_flash_read(esp_flash_default_chip, &pdst[read], disk_offset, copy)!=ESP_OK)
		{
		DebugPrint("esp_flash_read() failed\n");
		break;
		}
	read+=copy;
	}
return read;
}

BOOL FlashDevice::SetSize(FILE_SIZE size)
{
return false;
}

SIZE_T FlashDevice::Write(FILE_SIZE offset, VOID const* pbuf, SIZE_T size)
{
if(!pbuf||!size)
	return 0;
BYTE* psrc=(BYTE*)pbuf;
UINT written=0;
while(written<size)
	{
	UINT disk_offset=(UINT)offset;
	UINT available=DiskOffset(&disk_offset);
	UINT copy=MIN(available, size-written);
	if(esp_flash_write(esp_flash_default_chip, &psrc[written], disk_offset, copy)!=ESP_OK)
		{
		DebugPrint("spi_flash_write() failed\n");
		break;
		}
	written+=copy;
	}
return written;
}


//==========================
// Con-/Destructors Private
//==========================

FlashDevice::FlashDevice():
uOffset(0),
uSize(0)
{
UINT size=0;
if(esp_flash_get_size(esp_flash_default_chip, &size)!=ESP_OK)
	{
	DebugPrint("esp_flash_get_size() failed\n");
	return;
	}
esp_partition_iterator_t it=esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, nullptr);
esp_partition_t const* plast=nullptr;
while(it)
	{
	plast=esp_partition_get(it);
	it=esp_partition_next(it);
	}
if(!plast)
	{
	DebugPrint("esp_partition_find failed\n");
	return;
	}
uOffset=BlockAlign(plast->address+plast->size, SPI_FLASH_SEC_SIZE);
uSize=size-uOffset;
}


//================
// Common Private
//================

UINT FlashDevice::DiskOffset(UINT* offset)
{
if(*offset>=uSize)
	return 0;
UINT block=*offset/SPI_FLASH_SEC_SIZE;
UINT block_pos=*offset%SPI_FLASH_SEC_SIZE;
*offset=uOffset+uSize-(block+1)*SPI_FLASH_SEC_SIZE+block_pos;
return SPI_FLASH_SEC_SIZE-block_pos;
}

Handle<FlashDevice> FlashDevice::hCurrent;

}}