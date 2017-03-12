#pragma once

#include"ShareMemory.h"
#include "OperateFunc.h"

#define VID						NULL
#define PID						NULL
#define HEX_EDIT_LIMIT_SIZE		(4096)

#define READ_TIMER_ID			1
#define READ_TIMER_ELAPSE		50

#define READ_TIMEOUT			0
#define WRITE_TIMEOUT			2000

#define READ_SIZE				1000

typedef int HID_UART_STATUS;

// Return Codes
#define HID_UART_SUCCESS							0x00
#define	HID_UART_DEVICE_NOT_FOUND					0x01
#define HID_UART_INVALID_HANDLE						0x02
#define	HID_UART_INVALID_DEVICE_OBJECT				0x03
#define	HID_UART_INVALID_PARAMETER					0x04
#define	HID_UART_INVALID_REQUEST_LENGTH				0x05

#define	HID_UART_READ_ERROR							0x10
#define	HID_UART_WRITE_ERROR						0x11
#define	HID_UART_READ_TIMED_OUT						0x12
#define	HID_UART_WRITE_TIMED_OUT					0x13
#define	HID_UART_DEVICE_IO_FAILED					0x14
#define HID_UART_DEVICE_ACCESS_ERROR				0x15
#define HID_UART_DEVICE_NOT_SUPPORTED				0x16

#define HID_UART_UNKNOWN_ERROR						0xFF

/////////////////////////////////////////////////////////////////////////////
// String Definitions
/////////////////////////////////////////////////////////////////////////////

// Product String Types
#define HID_UART_GET_VID_STR						0x01
#define HID_UART_GET_PID_STR						0x02
#define HID_UART_GET_PATH_STR						0x03
#define HID_UART_GET_SERIAL_STR						0x04
#define HID_UART_GET_MANUFACTURER_STR				0x05
#define HID_UART_GET_PRODUCT_STR					0x06

// String Lengths
#define HID_UART_DEVICE_STRLEN						260

// HID_UART_DEVICE_STR
typedef char HID_UART_DEVICE_STR[HID_UART_DEVICE_STRLEN];

/////////////////////////////////////////////////////////////////////////////
// UART Definitions
/////////////////////////////////////////////////////////////////////////////

// Error Status
#define HID_UART_PARITY_ERROR						0x01
#define HID_UART_OVERRUN_ERROR						0x02

// Line Break Status
#define HID_UART_LINE_BREAK_INACTIVE				0x00
#define HID_UART_LINE_BREAK_ACTIVE					0x01

// Data Bits
#define HID_UART_FIVE_DATA_BITS						0x00
#define HID_UART_SIX_DATA_BITS						0x01
#define HID_UART_SEVEN_DATA_BITS					0x02
#define HID_UART_EIGHT_DATA_BITS					0x03

// Parity
#define HID_UART_NO_PARITY							0x00
#define HID_UART_ODD_PARITY							0x01
#define HID_UART_EVEN_PARITY						0x02
#define HID_UART_MARK_PARITY						0x03
#define HID_UART_SPACE_PARITY						0x04

// Stop Bits
// Short = 1 stop bit
// Long  = 1.5 stop bits (5 data bits)
//       = 2 stop bits (6-8 data bits)
#define HID_UART_SHORT_STOP_BIT						0x00
#define HID_UART_LONG_STOP_BIT						0x01

// Flow Control
#define HID_UART_NO_FLOW_CONTROL					0x00
#define HID_UART_RTS_CTS_FLOW_CONTROL				0x01

// Read/Write Limits
#define HID_UART_MIN_READ_SIZE						1
#define HID_UART_MAX_READ_SIZE						32768
#define HID_UART_MIN_WRITE_SIZE						1
#define HID_UART_MAX_WRITE_SIZE						4096

/////////////////////////////////////////////////////////////////////////////
// Part Number Definitions
/////////////////////////////////////////////////////////////////////////////

// Part Numbers
#define HID_UART_PART_CP2110						0x0A

/////////////////////////////////////////////////////////////////////////////
// User Customization Definitions
/////////////////////////////////////////////////////////////////////////////

// User-Customizable Field Lock Bitmasks
#define HID_UART_LOCK_PRODUCT_STR_1					0x0001
#define HID_UART_LOCK_PRODUCT_STR_2					0x0002
#define HID_UART_LOCK_SERIAL_STR					0x0004
#define HID_UART_LOCK_PIN_CONFIG					0x0008
#define HID_UART_LOCK_VID							0x0100
#define HID_UART_LOCK_PID							0x0200
#define HID_UART_LOCK_POWER							0x0400
#define HID_UART_LOCK_POWER_MODE					0x0800
#define HID_UART_LOCK_RELEASE_VERSION				0x1000
#define HID_UART_LOCK_FLUSH_BUFFERS					0x2000
#define HID_UART_LOCK_MFG_STR_1						0x4000
#define HID_UART_LOCK_MFG_STR_2						0x8000

// Field Lock Bit Values
#define HID_UART_LOCK_UNLOCKED						1
#define HID_UART_LOCK_LOCKED						0

// Power Max Value (500 mA)
#define HID_UART_BUS_POWER_MAX						0xFA

// Power Modes
#define HID_UART_BUS_POWER							0x00
#define HID_UART_SELF_POWER_VREG_DIS				0x01
#define HID_UART_SELF_POWER_VREG_EN					0x02

// Flush Buffers Bitmasks
#define HID_UART_FLUSH_TX_OPEN						0x01
#define HID_UART_FLUSH_TX_CLOSE						0x02
#define HID_UART_FLUSH_RX_OPEN						0x04
#define HID_UART_FLUSH_RX_CLOSE						0x08

// USB Config Bitmasks
#define HID_UART_SET_VID							0x01
#define HID_UART_SET_PID							0x02
#define HID_UART_SET_POWER							0x04
#define HID_UART_SET_POWER_MODE						0x08
#define HID_UART_SET_RELEASE_VERSION				0x10
#define HID_UART_SET_FLUSH_BUFFERS					0x20

// USB Config Bit Values
#define HID_UART_SET_IGNORE							0
#define HID_UART_SET_PROGRAM						1

// String Lengths
#define HID_UART_MFG_STRLEN							62
#define HID_UART_PRODUCT_STRLEN						62
#define HID_UART_SERIAL_STRLEN						30

// HID_UART_MFG_STR
typedef char HID_UART_MFG_STR[HID_UART_MFG_STRLEN];

// HID_UART_PRODUCT_STR
typedef char HID_UART_PRODUCT_STR[HID_UART_PRODUCT_STRLEN];

// HID_UART_SERIAL_STR
typedef char HID_UART_SERIAL_STR[HID_UART_SERIAL_STRLEN];

/////////////////////////////////////////////////////////////////////////////
// Pin Definitions
/////////////////////////////////////////////////////////////////////////////

// Pin Config Mode Array Indices
#define HID_UART_INDEX_GPIO_0_CLK					0
#define HID_UART_INDEX_GPIO_1_RTS					1
#define HID_UART_INDEX_GPIO_2_CTS					2
#define HID_UART_INDEX_GPIO_3_RS485					3
#define HID_UART_INDEX_GPIO_4_TX_TOGGLE				4
#define HID_UART_INDEX_GPIO_5_RX_TOGGLE				5
#define HID_UART_INDEX_GPIO_6						6
#define HID_UART_INDEX_GPIO_7						7
#define HID_UART_INDEX_GPIO_8						8
#define HID_UART_INDEX_GPIO_9						9
#define HID_UART_INDEX_TX							10
#define HID_UART_INDEX_SUSPEND						11
#define HID_UART_INDEX_SUSPEND_BAR					12

// Pin Config Modes
#define HID_UART_GPIO_MODE_INPUT					0x00
#define HID_UART_GPIO_MODE_OUTPUT_OD				0x01
#define HID_UART_GPIO_MODE_OUTPUT_PP				0x02
#define HID_UART_GPIO_MODE_FUNCTION					0x03

// Pin Bitmasks
#define HID_UART_MASK_GPIO_0_CLK					0x0001
#define HID_UART_MASK_GPIO_1_RTS					0x0002
#define HID_UART_MASK_GPIO_2_CTS					0x0004
#define HID_UART_MASK_GPIO_3_RS485					0x0008
#define HID_UART_MASK_TX							0x0010
#define HID_UART_MASK_RX							0x0020
#define HID_UART_MASK_GPIO_4_TX_TOGGLE				0x0040
#define HID_UART_MASK_GPIO_5_RX_TOGGLE				0x0080
#define HID_UART_MASK_SUSPEND_BAR					0x0100
// NA												0x0200
#define HID_UART_MASK_GPIO_6						0x0400
#define HID_UART_MASK_GPIO_7						0x0800
#define HID_UART_MASK_GPIO_8						0x1000
#define HID_UART_MASK_GPIO_9						0x2000
#define HID_UART_MASK_SUSPEND						0x4000

// Suspend Value Bit Values
#define HID_UART_VALUE_SUSPEND_LO					0
#define HID_UART_VALUE_SUSPEND_HI					1

// Suspend Mode Bit Values
#define HID_UART_MODE_SUSPEND_OD					0
#define HID_UART_MODE_SUSPEND_PP					1

// RS485 Active Levels
#define HID_UART_MODE_RS485_ACTIVE_LO				0x00
#define HID_UART_MODE_RS485_ACTIVE_HI				0x01

/////////////////////////////////////////////////////////////////////////////
// Typedefs
/////////////////////////////////////////////////////////////////////////////

typedef void* HID_UART_DEVICE;

//////////////////////////////////
//Multimeter
//////////////////////////////////
typedef int DATA_RETURN_TYPE;

//device to PC
#define RESPONSE_TYPE						0x01
#define REALTIME_TYPE						0x02
#define READBACK_TYPE						0x03
#define SUMMARY_TYPE						0x04
#define DOT_TYPE						    0x05
#define QUERY_TYPE						    0x72

//PC to device
#define MEASURE_FUNCTION					0x01
#define MEASURE_RANGE						0x02
#define REL_REF_SET 						0x03
#define MAX_MIN     						0x04
#define REAL_TIME						    0x05
#define SAVE_DATA						    0x06
#define READBACK_DATA   					0x07
#define QUERY_MEAS_DATA_NUM					0x08
#define DELETE_SAVED_DATA					0x09
#define START_RECORD   						0x0A
#define STOP_RECORD						    0x0B
#define READBACK_RECORD_SUMMARY			    0x0C
#define READBACK_RECORD_DOT   				0x0D
#define QUERY_RECORD_NUM				    0x0E
#define DELETE_SAVED_RECORD				    0x0F
#define DATE_TIME_SET   				    0x10
#define QUERY_DEVICE_INFO				    0x11
#define TRIGGER_HOLD				        0x12






class CHidUart
{
public:
	CHidUart(void);
	~CHidUart(void);

	CString GetHidUartStatusStr(HID_UART_STATUS status);        //获取设备操作返回状态信息
	CString CleanHexString(const CString editStr);              //清除16进制字符串无用信息


	//串口操作
	int DevicesGetNum(char* deviceName,DWORD* NumDevices);                      //获取Hid设备数量
	int DeviceOpen(char* deviceName,DWORD deviceNum);                       //通过设备编号打开设备
	int DeviceGetString(char* deviceName,DWORD deviceNum, char* deviceString);    //获取HID芯片序列号
	int DeviceClose(char* deviceName);                      //关闭设备
	int DeviceConnect(char* deviceName);                    //连接设备，设置串口，设置读写时间
	int DeviceWriteString(char* deviceName,char* HexString);                      //写入串口数据字符串
    int DeviceWrite(char* deviceName, BYTE* buffer,DWORD numBytesToWrite);       //写入串口数据
	int DeviceRead(char* deviceName,BYTE* databuffer,DWORD* numBytesRead);      //读出串口返回数据

private:
	char m_com[100];       //设备物理地址
	char m_dllPath[255];   //设备dll地址
	char m_funcName[100];  //功能名
	char m_channel[100];   //通道
	char m_deviceHandle[100];  //设备物理句柄
	HID_UART_DEVICE	m_hidUart;
	HMODULE m_InitModule; //初始化dll句柄
	ShareMemory m_CShare;     //共享内存空间处理对象
	COperateFunc m_COperate;  //操作函数对象
	

	
};
