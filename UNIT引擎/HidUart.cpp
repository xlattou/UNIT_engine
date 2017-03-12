#include "stdafx.h"
#include "HidUart.h"

CHidUart::CHidUart(void)
{
}

CHidUart::~CHidUart(void)
{
}
//状态说明
CString CHidUart::GetHidUartStatusStr(HID_UART_STATUS status)
{
	CString statusStr = _T("Unknown status");

	switch (status)
	{
	case HID_UART_SUCCESS:					statusStr = _T("Success");					break;
	case HID_UART_DEVICE_NOT_FOUND:			statusStr = _T("Device not found");			break;
	case HID_UART_INVALID_HANDLE:			statusStr = _T("Invalid handle");			break;
	case HID_UART_INVALID_DEVICE_OBJECT:	statusStr = _T("Invalid device object");	break;
	case HID_UART_INVALID_PARAMETER:		statusStr = _T("Invalid parameter");		break;
	case HID_UART_INVALID_REQUEST_LENGTH:	statusStr = _T("Invalid request length");	break;

	case HID_UART_READ_ERROR:				statusStr = _T("Read error");				break;
	case HID_UART_WRITE_ERROR:				statusStr = _T("Write error");				break;
	case HID_UART_READ_TIMED_OUT:			statusStr = _T("Read timed out");			break;
	case HID_UART_WRITE_TIMED_OUT:			statusStr = _T("Write timed out");			break;
	case HID_UART_DEVICE_IO_FAILED:			statusStr = _T("Device I/O failed");		break;
	case HID_UART_DEVICE_ACCESS_ERROR:		statusStr = _T("Device access error");		break;
	case HID_UART_DEVICE_NOT_SUPPORTED:		statusStr = _T("Device not supported");		break;

	case HID_UART_UNKNOWN_ERROR:			statusStr = _T("Unknown error");			break;
	}

	return statusStr;
}

CString CHidUart::CleanHexString(const CString editStr)
{
	CString cleanStr = editStr;

	// 去除空格
	cleanStr.Replace(_T(" "), _T(""));

	// 去除逗号
	cleanStr.Replace(_T(","), _T(""));

	// 去除回车、换行
	cleanStr.Replace(_T("\r"), _T(""));
	cleanStr.Replace(_T("\n"), _T(""));

	// 限制在16进制字符内
	// 在第一个非法字符停止
	cleanStr = cleanStr.SpanIncluding(_T("0123456789abcdefABCDEF"));

	// 输入个数为奇数时的处理
	if (cleanStr.GetLength() % 2 == 1)
	{
		// 在最后一个字符前加0
		cleanStr = cleanStr.Left(cleanStr.GetLength() - 1) + _T("0") + cleanStr[cleanStr.GetLength() -1];
	}

	return cleanStr;
}


int CHidUart::DevicesGetNum(char* deviceName,DWORD* NumDevices)
{
	int ret=1;
	m_COperate.FuncConvert(deviceName,"GetNumDevices",m_dllPath,m_funcName);//获取函数所属的dll和名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GetNumDevices对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	
	HidUart1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(HidUart1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(NumDevices,VID,PID);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到获取设备数量函数");
		}
	}
	else
	{
		throw string("加载获取设备数量程序库失败");
	}
	return ret;
}


int CHidUart::DeviceGetString(char* deviceName,DWORD deviceNum, char* deviceString)
{
	int ret=1;
	HID_UART_STATUS status;	
	m_COperate.FuncConvert(deviceName,"GetString",m_dllPath,m_funcName);//获取函数所属的dll和名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GetString对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	HidUart2 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(HidUart2)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			status=lpFunc(deviceNum, VID, PID, deviceString, HID_UART_GET_SERIAL_STR);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到获取Hid_Uart序列号函数");
		}
		if (status == HID_UART_SUCCESS)
		{
			ret=0;			
		}
		else
		{
			ret=1;
			CString msg;
			msg.Format(_T("Failed to transmit : %s"),GetHidUartStatusStr(ret));
			//AfxMessageBox(msg, 0, MB_ICONWARNING);
		}
	}
	else
	{
		throw string("加载获取Hid_Uart序列号程序库失败");
	}

	return ret;
}

int CHidUart::DeviceOpen(char* deviceName,DWORD deviceNum)
{
	int ret=1;

	m_COperate.FuncConvert(deviceName,"DeviceOpen",m_dllPath,m_funcName);//获取函数所属的dll和名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DeviceOpen对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	HidUart3 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(HidUart3)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(&m_hidUart,deviceNum,VID, PID);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到打开设备函数");
		}
	}
	else
	{
		throw string("加载打开设备程序库失败");
	}
	return ret;
}

int CHidUart::DeviceClose(char* deviceName)
{
	int ret=1;
	m_COperate.FuncConvert(deviceName,"DeviceClose",m_dllPath,m_funcName);//获取函数所属的dll和名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DeviceClose对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	HidUart4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(HidUart4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_hidUart);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到关闭设备函数");
		}
	}
	else
	{
		throw string("加载关闭设备程序库失败");
	}
	return ret;
}

int CHidUart::DeviceConnect(char* deviceName)
{
	
	int ret=1;
	HID_UART_STATUS status;
	DWORD baudRate=9600;
	BYTE dataBits=HID_UART_EIGHT_DATA_BITS;
	BYTE parity=HID_UART_NO_PARITY;
	BYTE stopBits=HID_UART_SHORT_STOP_BIT;
	BYTE flowControl=HID_UART_NO_FLOW_CONTROL;
	m_COperate.FuncConvert(deviceName,"SetUartConfig",m_dllPath,m_funcName);//获取函数所属的dll和名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到SetUartConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	HidUart5 lpFunc1=NULL;
	if(hModule)
	{
		lpFunc1=(HidUart5)GetProcAddress(hModule,m_funcName);
		if(lpFunc1)
		{
			status=lpFunc1(m_hidUart, baudRate, dataBits, parity, stopBits, flowControl);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到串口设置函数");
		}
	}
	else
	{
		throw string("加载串口设置程序库失败");
	}
	if (status == HID_UART_SUCCESS)
	{
		ret=0;
		DWORD vBaudRate;
		BYTE vDataBits;
		BYTE vParity;
		BYTE vStopBits;
		BYTE vFlowControl;
		m_COperate.FuncConvert(deviceName,"GetUartConfig",m_dllPath,m_funcName);//获取函数所属的dll和名称
    	if(((string)m_funcName).empty())
	    {
		    throw string("找不到GetUartConfig对应的驱动信息");
	    }
		hModule=LoadLibrary(_T(m_dllPath));//调用dll
	    HidUart6 lpFunc2=NULL;
	    if(hModule)
	    {
		    lpFunc2=(HidUart6)GetProcAddress(hModule,m_funcName);
		    if(lpFunc2)
		    {
			    status=lpFunc2(m_hidUart, &vBaudRate, &vDataBits, &vParity, &vStopBits, &vFlowControl);
		    }
		    else
		    {
			    if(!FreeLibrary(hModule))
				    throw string("卸载动态链接库失败");
			    throw string("找不到获取串口设置函数");
		    }
	    }
	    else
	    {
		    throw string("加载获取串口设置程序库失败");
	    }
		if (status == HID_UART_SUCCESS)
		{
			ret=0;
			if (vBaudRate != baudRate ||
				vDataBits != dataBits ||
				vParity != parity ||
				vStopBits != stopBits ||
				vFlowControl != flowControl)
			{
				ret = HID_UART_INVALID_PARAMETER;
				throw string("INVALID PARAMETER");
			}
		}
	}

    if (status == HID_UART_SUCCESS)
	{
		m_COperate.FuncConvert(deviceName,"SetTimeouts",m_dllPath,m_funcName);//获取函数所属的dll和名称
		if(((string)m_funcName).empty())
		{
			throw string("找不到SetTimeouts对应的驱动信息");
		}
		hModule=LoadLibrary(_T(m_dllPath));//调用dll
		HidUart7 lpFunc3=NULL;
		if(hModule)
		{
			lpFunc3=(HidUart7)GetProcAddress(hModule,m_funcName);
			if(lpFunc3)
			{
				status=lpFunc3(m_hidUart, READ_TIMEOUT, WRITE_TIMEOUT);
			}
			else
			{
				if(!FreeLibrary(hModule))
					throw string("卸载动态链接库失败");
				throw string("找不到时间设置函数");
			}
		}
		else
		{
			throw string("加载时间设置程序库失败");
		}

	}
	
	return ret;
}


int CHidUart::DeviceWriteString(char* deviceName,char* HexString)
{
	int ret=1;
	HID_UART_STATUS status;
	CString transmitStr=HexString;
	transmitStr=CleanHexString(transmitStr);   //清除16进制字符串无用信息
	DWORD numBytesWritten=0;
	DWORD numBytesToWrite=transmitStr.GetLength()/2;
	BYTE* buffer= new BYTE[numBytesToWrite];

    // 转换16进制位字符串为BYTE类型
	for (DWORD i = 0; i < numBytesToWrite; i++)
	{
		CString hexByte = transmitStr.Mid(i * 2, 2);
		buffer[i] = (BYTE)_tcstol(hexByte, NULL, 16);
	}
	m_COperate.FuncConvert(deviceName,"DeviceWrite",m_dllPath,m_funcName);//获取函数所属的dll和名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DeviceWrite对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	HidUart8 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(HidUart8)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			status=lpFunc(m_hidUart,buffer,numBytesToWrite,&numBytesWritten);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到设备写入函数");
		}
		if (status == HID_UART_SUCCESS)
		{
			ret=0;			
		}
		else
		{
			ret=1;
			CString msg;
			msg.Format(_T("Failed to transmit : %s"),GetHidUartStatusStr(ret));
			//AfxMessageBox(msg, 0, MB_ICONWARNING);
		}
	}
	else
	{
		throw string("加载设备写入程序库失败");
	}
	delete []buffer;
	return ret;
}


int CHidUart::DeviceRead(char* deviceName,BYTE* databuffer,DWORD* numBytesRead)
{
	int ret=1;
	HID_UART_STATUS status;
	DWORD numBytesToRead=READ_SIZE;   
	m_COperate.FuncConvert(deviceName,"DeviceRead",m_dllPath,m_funcName);//获取函数所属的dll和名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DeviceRead对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	HidUart9 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(HidUart9)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			status=lpFunc(m_hidUart,databuffer,numBytesToRead,numBytesRead);
			
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到设备写入函数");
		}
		if (status == HID_UART_SUCCESS || status == HID_UART_READ_TIMED_OUT)
		{
			ret=0;
			
		}
		else
		{
			ret=1;
			CString msg;
			msg.Format(_T("Failed to Read : %s"),GetHidUartStatusStr(ret));
			AfxMessageBox(msg, 0, MB_ICONWARNING);
		}
	}
	else
	{
		throw string("加载设备写入程序库失败");
	}
	return ret;
}

int CHidUart::DeviceWrite(char* deviceName, BYTE* buffer,DWORD numBytesToWrite)
{
	int ret=1;
	HID_UART_STATUS status;
	DWORD numBytesWritten=0;

	m_COperate.FuncConvert(deviceName,"DeviceWrite",m_dllPath,m_funcName);//获取函数所属的dll和名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DeviceWrite对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	HidUart8 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(HidUart8)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			status=lpFunc(m_hidUart,buffer,numBytesToWrite,&numBytesWritten);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到设备写入函数");
		}
		if (status == HID_UART_SUCCESS)
		{
			ret=0;			
		}
		else
		{
			ret=1;
			CString msg;
			msg.Format(_T("Failed to transmit : %s"),GetHidUartStatusStr(ret));
			//AfxMessageBox(msg, 0, MB_ICONWARNING);
		}
	}
	else
	{
		throw string("加载设备写入程序库失败");
	}
	return ret;
}
