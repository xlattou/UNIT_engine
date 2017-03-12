#include "stdafx.h"
#include "Switch.h"

Switch::Switch(char* device,ShareMemory &myShare):m_CShare(myShare)
{
    strcpy(deviceName,device);
}
int Switch::SwitchSet(char *Mark)
{

	try
	{
		m_CShare.WriteToSharedMemory("开关控制:%s;",Mark);
    	myOperate.FuncConvert(deviceName,"SwitchSet",com,channel,dllPath,funcName);
		if(((string)funcName).empty())
		{
			throw string("找不到SwitchSet对应的驱动信息");
		}
		HMODULE hModule=LoadLibrary(dllPath);//调用dll
		MySet4 lpFunc=NULL;
		if(hModule)
		{
			lpFunc=(MySet4)GetProcAddress(hModule,funcName);
			if(lpFunc)
			{
				lpFunc(com,Mark);
			}
			else
			{
				throw string("找不到开关控制函数");
			}
			if(!FreeLibrary(hModule))
	    		throw string("卸载动态链接库失败");
		}
		else
		{
			throw string("加载开关控制程序失败");
		}
    	//m_CShare.WriteToSharedMemory("开关控制:%s 操作成功;",Mark);
	}
	catch(char* e)
	{
		MessageBox(0,e,"error",0);
		return 0;		
	}

	return 1;
}

Switch::~Switch(void)
{
}

int Switch::SwitchTemperature(char* temperature)
{
	int ret=1;
	myOperate.FuncConvert(deviceName,"SwitchTemperature",dllPath,funcName);
	if(((string)funcName).empty())
	{
		throw string("找不到SwitchTemperature对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(dllPath);//调用dll
	MyPowerTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyPowerTest)GetProcAddress(hModule,funcName);
		if(lpFunc)
		{
			ret=lpFunc(com,temperature,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("卸载动态链接库失败");
			throw string("找不到开关获取温度函数");
		}
	}
	else
	{
		throw string("加载开关获取温度程序库失败");
	}
	//m_CShare.WriteToSharedMemory("测试结果%s",data);
	return ret;
}
