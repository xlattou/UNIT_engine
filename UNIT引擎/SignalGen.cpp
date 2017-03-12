#include "stdafx.h"
#include "SignalGen.h"

CSignalGen::CSignalGen(char* device,ShareMemory &myshare):m_CShare(myshare)
{
	strcpy(m_deviceName,device);
}

CSignalGen::~CSignalGen(void)
{

}

void CSignalGen::RegGetSN(char VISA[], char SN[], int16_t *ret, int32_t len)
{
	m_COperate.FuncConvert(m_deviceName,"GetSN",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GetSN对应的驱动信息");
	}

	int ret1=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet15 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet15)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret1=lpFunc(VISA,SN,ret,len);
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
}

int16_t CSignalGen::RegRFDigModeOutSet(char VISA[], char ModeStateOut[])
{
	m_COperate.FuncConvert(m_deviceName,"RFDigModeOutSet",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到RFDigModeOutSet对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeStateOut);
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int16_t CSignalGen::RegRFGenClose(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenClose",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到RFGenClose对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet10 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet10)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA);
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int16_t CSignalGen::RegRFGenDigModeSet(char VISA[], char ModeStateArb[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenDigModeSet",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到RFGenDigModeSet对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeStateArb);
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

void CSignalGen::RegRFGenInit(char VISA[], char ModeReset[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenInit",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	
	if(((string)m_funcName).empty())
	{
		throw string("找不到RFGenInit对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeReset);
		}
		else
		{
			throw string("RFGeninit找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
}

int16_t CSignalGen::RegRFGenOutSet(char VISA[], char ModeOutput[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenOutSet",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到RFGenOutSet对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeOutput);
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int16_t CSignalGen::RegRFGenSelectDigWave(char VISA[], char WaveName[])
{
	CString strTemp = "";
	strTemp.Format("%s",WaveName);
	AfxMessageBox(strTemp);

	m_COperate.FuncConvert(m_deviceName,"RFGenSelectDigWave",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到RFGenSelectDigWave对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,WaveName);
		}
		else
		{
			throw string("111找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int16_t CSignalGen::RegRFGenSet(char VISA[], char FreqHz[], char AmpDBm[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenSet",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称

	if(((string)m_funcName).empty())
	{
		throw string("找不到RFGenSet对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,FreqHz,AmpDBm);
		}
		else
		{
			throw string("5555找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}