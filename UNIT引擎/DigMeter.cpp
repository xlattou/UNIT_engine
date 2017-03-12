#include "stdafx.h"
#include "DigMeter.h"

CDigMeter::CDigMeter(char* device,ShareMemory &myshare):m_CShare(myshare)
{
	strcpy(m_deviceName,device);
}

CDigMeter::~CDigMeter(void)
{
}

int CDigMeter::DigMeterInit(char* isReset)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("1...");
	m_COperate.FuncConvert(m_deviceName,"DigMeterInit",m_com,m_channel,m_dllPath,m_funcName);//获取函数所属的dll和名称
	//	m_CShare.WriteToSharedMemory("2...");
	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //读取设备状态
	string temp_s(status);
	//	m_CShare.WriteToSharedMemory("3...");
	if(temp_s!="Open")
	{
		//m_CShare.WriteToSharedMemory("数字万用表初始化...");
		if(((string)m_funcName).empty())
		{
			throw string("找不到DigMeterInit对应的驱动信息");
		}
		m_InitModule=LoadLibrary(m_dllPath);//调用dll
		MyInit lpFunc=NULL;
		if(m_InitModule)
		{
			lpFunc=(MyInit)GetProcAddress(m_InitModule,m_funcName);
			if(lpFunc)
			{
				ret=lpFunc(m_com,isReset?"1":"0",m_deviceHandle,50);
			}
			else
			{
				if(!FreeLibrary(m_InitModule))
					throw string("卸载动态链接库失败");
				throw string("找不到初始化函数");
			}
		}
		else
		{
			throw string("加载数字万用表初始化程序库失败");
		}
		if(ret==0)
		{
			m_CShare.WriteToSharedMemory("数字万用表初始化完成");
			int isWrite1=m_COperate.WriteHandles(m_com,"DeviceOutHandle",m_deviceHandle);  //写入设备地址
			int isWrite2=m_COperate.WriteHandles(m_com,"DeviceStatus","Open"); //写入设备状态
			char hModule[20];
			sprintf_s(hModule,20,"%d",(int)(m_InitModule));
			m_COperate.WriteHandles(m_com,"InitDllHandle",hModule); //写入初始化dll句柄
			if((isWrite2|isWrite2)==0)
			{
				throw string("状态写入失败");
			}
		}
		else
		{
			m_CShare.WriteToSharedMemory("数字万用表初始化失败");
		}

	}
	else if(temp_s=="Open")
	{
		ret=0;
		m_COperate.ReadHandles(m_com,"DeviceOutHandle",m_deviceHandle);
		//	m_CShare.WriteToSharedMemory("4...");
		//m_CShare.WriteToSharedMemory("数字万用表已启动");
	}
	return ret;
}

int CDigMeter::DigMeterClose(int intSerial)
{
	int ret=1;
	if(intSerial!=-1)
		return 0;
	m_COperate.FuncConvert(m_deviceName,"DigMeterClose",m_com,m_channel,m_dllPath,m_funcName);//获取函数所属的dll和名称

	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //读取设备状态
	string temp_s(status);
	if(temp_s=="Close")
		return 0;
	char hInitModule[20];
	//m_CShare.WriteToSharedMemory("数字万用表关闭");
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterClose对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MyControl lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyControl)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle);
		}
		else
		{
			throw string("找不到数字万用表关闭函数");
		}
		if(!FreeLibrary(hModule))
			throw string("卸载动态链接库失败");
	//	if(ret==0)
	//	{
			m_COperate.ReadHandles(m_com,"InitDllHandle",hInitModule);  //读取初始化dll句柄
			m_InitModule=(HMODULE)(atoi(hInitModule));

			FreeLibrary(m_InitModule);
			//if(!FreeLibrary(m_InitModule))
			//	throw string("卸载初始化动态链接库失败");
			m_COperate.WriteHandles(m_com,"DeviceStatus","Close"); //写入设备状态
		    m_CShare.WriteToSharedMemory("数字万用表连接已关闭");
	//	}
	//	else
	//	{
	  //  	m_CShare.WriteToSharedMemory("关闭数字万用表连接失败");
	//	}

	}
	else
	{
		throw string("加载数字万用表关闭程序库失败");
	}
	return ret;
}

int CDigMeter::DigMeterConfig(char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"DigMeterConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet2 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet2)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Func,isAutoRange,ManuRange,unit,ManuResolution);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到数字万用表设置函数");
		}
	}
	else
	{
		throw string("加载数字万用表设置程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}

int CDigMeter::DigMeterAutoZero(char* Func)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"DigMeterAutoZero",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterAutoZero对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Func);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到数字万用表归零函数");
		}
	}
	else
	{
		throw string("加载数字万用表归零程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}

int CDigMeter::DigMeterCal(char* RangeValue)
{
	char data[50];
	int ret=1;
	//m_CShare.WriteToSharedMemory("数字万用表校准");
	m_COperate.FuncConvert(m_deviceName,"DigMeterCal",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterCal对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MyTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,RangeValue,data,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到数字万用表校准函数");
		}
	}
	else
	{
		throw string("加载数字万用表校准程序库失败");
	}
	CString strData=data;
	if(strData.IsEmpty())
	{
    	m_CShare.WriteToSharedMemory("安全密码解码失败");
	}
	else if(atoi(data)==0)
	{
    	m_CShare.WriteToSharedMemory("校准成功");
	}
	else
	{
    	m_CShare.WriteToSharedMemory("校准失败");
	}
	return 0;
}
int CDigMeter::DigMeterCalSave()
{
	//char data[50];
	int ret=1;
	//m_CShare.WriteToSharedMemory("数字万用表校准保存");
	m_COperate.FuncConvert(m_deviceName,"DigMeterCalSave",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterCalSave对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MyControl lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyControl)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到数字万用表校准保存函数");
		}
	}
	else
	{
		throw string("加载数字万用表校准保存程序库失败");
	}
	return ret;
}
int CDigMeter::DigMeterRead(char* data)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("数字万用表读取数据");
	m_COperate.FuncConvert(m_deviceName,"DigMeterRead",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterRead对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MyPowerTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyPowerTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,data,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到数字万用表测试函数");
		}
	}
	else
	{
		throw string("加载数字万用表测试程序库失败");
	}
	//m_CShare.WriteToSharedMemory("测试结果%s",data);
	return ret;
}

int CDigMeter::DigMeterConfig_M(char* Chan, char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"DigMeterConfig_M",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterConfig_M对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet6 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet6)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Chan,Func,isAutoRange,ManuRange,unit,ManuResolution);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到数字万用表设置函数");
		}
	}
	else
	{
		throw string("加载数字万用表设置程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}

int CDigMeter::DigMeterReadData(char* Chan,char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution,char* value)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"DigMeterReadData",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet7 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet7)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Chan,Func,isAutoRange,ManuRange,unit,ManuResolution,value,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到数字万用表读取函数");
		}
	}
	else
	{
		throw string("加载数字万用表读取程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}
int CDigMeter::DigMeterRead_M(char* Chan, char* data)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("数字万用表读取数据");
	m_COperate.FuncConvert(m_deviceName,"DigMeterRead_M",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterRead_M对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MyTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Chan,data,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到数字万用表测试函数");
		}
	}
	else
	{
		throw string("加载数字万用表测试程序库失败");
	}
	//m_CShare.WriteToSharedMemory("测试结果%s",data);
	return ret;
}