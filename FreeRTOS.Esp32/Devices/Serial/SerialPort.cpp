//================
// SerialPort.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <freertos/FreeRTOS.h>
#include <driver/uart.h>
#include "SerialPort.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Serial {


//==================
// Con-/Destructors
//==================

SerialPort::SerialPort(UINT id, BaudRate baud):
uId(id)
{
uart_config_t config;
ZeroMemory(&config, sizeof(uart_config_t));
config.baud_rate=(UINT)baud;
config.data_bits=UART_DATA_8_BITS;
config.flow_ctrl=UART_HW_FLOWCTRL_DISABLE;
config.parity=UART_PARITY_DISABLE;
#ifdef ESP32
config.source_clk=UART_SCLK_DEFAULT;
#endif
config.stop_bits=UART_STOP_BITS_1;
esp_err_t status=uart_param_config((uart_port_t)id, &config);
if(status!=ESP_OK)
	{
	DebugPrint("uart_param_config failed (%u)\r\n", status);
	return;
	}
/*#ifdef ESP32
status=uart_set_pin(uId, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
if(status!=ESP_OK)
	{
	DebugPrint("uart_set_pin failed (%u)\r\n", status);
	return;
	}
#endif
#ifdef ESP32
status=uart_set_sw_flow_ctrl(uId, false, 0, 0);
if(status!=ESP_OK)
	{
	DebugPrint("uart_set_sw_flow_ctrl failed (%u)\r\n", status);
	return;
	}
#endif*/
QueueHandle_t queue=nullptr;
status=uart_driver_install((uart_port_t)id, 2048, 2048, 10, &queue, 0);
if(status!=ESP_OK)
	{
	DebugPrint("uart_driver_install failed (%u)\r\n", status);
	return;
	}
}

SerialPort::~SerialPort()
{
uart_driver_delete((uart_port_t)uId);

}


//========
// Common
//========

VOID SerialPort::ClearBuffer()
{
ScopedLock lock(cMutex);
uart_flush_input((uart_port_t)uId);
}

Handle<SerialPort> SerialPort::Open()
{
if(!hDefault)
	hDefault=new SerialPort();
return hDefault;
}


//==============
// Input-Stream
//==============

SIZE_T SerialPort::Available()
{
ScopedLock lock(cMutex);
SIZE_T available=0;
if(uart_get_buffered_data_len((uart_port_t)uId, &available)!=ESP_OK)
	return 0;
return available;
}

SIZE_T SerialPort::Read(VOID* buf, SIZE_T size)
{
ScopedLock lock(cMutex);
return uart_read_bytes((uart_port_t)uId, (BYTE*)buf, size, 0);
}


//===============
// Output-Stream
//===============

VOID SerialPort::Flush()
{
ScopedLock lock(cMutex);
uart_flush((uart_port_t)uId);
}

SIZE_T SerialPort::Write(VOID const* buf, SIZE_T size)
{
ScopedLock lock(cMutex);
return uart_write_bytes((uart_port_t)uId, (LPCSTR)buf, size);
}


//================
// Common Private
//================

Handle<SerialPort> SerialPort::hDefault;

}}
