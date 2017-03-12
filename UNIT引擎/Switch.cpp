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
		m_CShare.WriteToSharedMemory("���ؿ���:%s;",Mark);
    	myOperate.FuncConvert(deviceName,"SwitchSet",com,channel,dllPath,funcName);
		if(((string)funcName).empty())
		{
			throw string("�Ҳ���SwitchSet��Ӧ��������Ϣ");
		}
		HMODULE hModule=LoadLibrary(dllPath);//����dll
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
				throw string("�Ҳ������ؿ��ƺ���");
			}
			if(!FreeLibrary(hModule))
	    		throw string("ж�ض�̬���ӿ�ʧ��");
		}
		else
		{
			throw string("���ؿ��ؿ��Ƴ���ʧ��");
		}
    	//m_CShare.WriteToSharedMemory("���ؿ���:%s �����ɹ�;",Mark);
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
		throw string("�Ҳ���SwitchTemperature��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(dllPath);//����dll
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
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ������ػ�ȡ�¶Ⱥ���");
		}
	}
	else
	{
		throw string("���ؿ��ػ�ȡ�¶ȳ����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("���Խ��%s",data);
	return ret;
}
