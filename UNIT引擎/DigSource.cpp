#include "stdafx.h"
#include "DigSource.h"

CDigSource::CDigSource(char* device,ShareMemory &myshare):m_CShare(myshare)
{
		strcpy(m_deviceName,device);
}

CDigSource::~CDigSource(void)
{
}

int CDigSource::DigSourceInit(char* isReset)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceInit",m_com,m_channel,m_dllPath,m_funcName);//获取函数所属的dll和名称
    
	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //读取设备状态
	string temp_s(status);
	if(temp_s!="Open")
	{
		//m_CShare.WriteToSharedMemory("校准源初始化...");
		if(((string)m_funcName).empty())
		{
			throw string("找不到DigSourceInit对应的驱动信息");
		}
		m_InitModule=LoadLibrary(_T(m_dllPath));//调用dll
		
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
			throw string("加载校准源初始化程序库失败");
		}
		if(ret==0)
		{
			m_CShare.WriteToSharedMemory("校准源初始化完成");
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
			m_CShare.WriteToSharedMemory("校准源初始化失败");
		}

	}
	else if(temp_s=="Open")
	{
		ret=2;
		m_COperate.ReadHandles(m_com,"DeviceOutHandle",m_deviceHandle);
		//m_CShare.WriteToSharedMemory("校准源连接已启动");
	}
	return ret;
}

int CDigSource::DigSourceClose(int intSerial)
{
	int ret=1;
	if(intSerial!=-1)
		return 0;
	m_COperate.FuncConvert(m_deviceName,"DigSourceClose",m_com,m_channel,m_dllPath,m_funcName);//获取函数所属的dll和名称

	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //读取设备状态
	string temp_s(status);
	if(temp_s=="Close")
		return 0;
	char hInitModule[20];
	//m_CShare.WriteToSharedMemory("校准源连接关闭");
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigSourceClose对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
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
			throw string("找不到校准源关闭函数");
		}
		if(!FreeLibrary(hModule))
			throw string("卸载动态链接库失败");

		//if(ret==0)
	//	{
			m_COperate.ReadHandles(m_com,"InitDllHandle",hInitModule);  //读取初始化dll句柄
			m_InitModule=(HMODULE)(atoi(hInitModule));
			FreeLibrary(m_InitModule);
			//if(!FreeLibrary(m_InitModule))
			//	throw string("卸载初始化动态链接库失败");
			m_COperate.WriteHandles(m_com,"DeviceStatus","Close"); //写入设备状态
			m_CShare.WriteToSharedMemory("校准源连接已关闭");

	//	}
	//	else
	//	{
	//		m_CShare.WriteToSharedMemory("校准源连接关闭失败");

	//	}

	}
	else
	{
		throw string("加载校准源关闭程序库失败");
	}

	return ret;
}

int CDigSource::DigSourceConfig(char* function, char* value, char* unit, char* freq,char* unit_Freq,char* currentPort)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigSourceConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	MySet6 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet6)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,function,value,unit,freq,unit_Freq,currentPort);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到校准源设置函数");
		}
	}
	else
	{
		throw string("加载校准源设置程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}

int CDigSource::DigSourceOutSet(char* isOutSet)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceOutSet",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigSourceOutSet对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isOutSet);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到校准源输出控制函数");
		}
	}
	else
	{
		throw string("加载校准源输出控制程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}
int CDigSource::DigSourceOffset(char* offsetValue)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceOffset",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigSourceOffset对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,offsetValue);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到校准源直流偏置设置函数");
		}
	}
	else
	{
		throw string("加载校准源直流偏置设置程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}
int CDigSource::DigSourceWaveSet(char* wave,char* duty)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceWaveSet",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigSourceWaveSet对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	MySet1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,wave,duty);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到校准源直流偏置设置函数");
		}
	}
	else
	{
		throw string("加载校准源直流偏置设置程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}
int CDigSource::DigSourceReset(char* isReset)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceReset",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigSourceReset对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isReset);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到校准源重置函数");
		}
	}
	else
	{
		throw string("加载校准源重置程序库失败");
	}
	//m_CShare.WriteToSharedMemory("设置完成");
	return ret;
}