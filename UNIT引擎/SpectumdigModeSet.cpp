#include "stdafx.h"
#include "SpectrumdigModeSet.h"

CSpectrumdigModeSet::CSpectrumdigModeSet(char* device,ShareMemory &myshare):m_CShare(myshare)
{
	strcpy(m_deviceName,device);

}

CSpectrumdigModeSet::~CSpectrumdigModeSet()
{

}

int CSpectrumdigModeSet::RegSpecModeSet(char VISA[], char ModeName[])
{
	m_COperate.FuncConvert(m_deviceName,"SpecModeSet",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
	}
	

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeName);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);

	return 0;
}

int16_t CSpectrumdigModeSet::RegLTESetULink(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"LTESetULink",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
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
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);

	return 0;
}

int16_t CSpectrumdigModeSet::RegLTESetB10M(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"LTESetB10M",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
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
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);

	return 0;
}

int16_t CSpectrumdigModeSet::RegWCDMAradioMS(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"WCDMAradioMS",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
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
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);

	return 0;
}

void CSpectrumdigModeSet::RegGSMMeasResult(char VISA[], char PhaseErr[], char FreqErr[], char EVM[])
{
	m_COperate.FuncConvert(m_deviceName,"GSMMeasResult",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMMeasResult对应的驱动信息");
	}
	int16_t ret = -1;
	CString str;
	//
	int ret1=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet11 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet11)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA,PhaseErr,FreqErr,EVM,(&ret),100,100,100);
			CString str;
			str.Format("%s", PhaseErr);
			AfxMessageBox(str);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegLTEMeasResult(char VISA[], char EVM[], char FreError[])
{
	m_COperate.FuncConvert(m_deviceName,"LTEMeasResult",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到RegLTEMeasResult对应的驱动信息");
	}
	int16_t ret = -1;
	int ret1=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet12 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet12)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA,EVM,FreError,&ret,100,100);
			CString strTemp;
			strTemp.Format("%s", EVM);
			AfxMessageBox(strTemp);
			strTemp.Format("%s", FreError);
			AfxMessageBox(strTemp);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegCDMA2000MeasResult(char VISA[], char EVM[], char Rho[],char FreError[])
{
	m_COperate.FuncConvert(m_deviceName,"CDMA2000MeasResult",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到CDMA2000MeasResult对应的驱动信息");
	}
	int16_t ret = -1;
	int ret1=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet13 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet13)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA,EVM,Rho,FreError,&ret,100,100,100);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegWCDMAMeasResult(char VISA[], char EVM[], char Rho[],char MagError[], char FreError[])
{
	int32_t len = 100;
	int32_t len2 = 100;
	int32_t len3= 100;
	int32_t len4 = 100;
	int16_t ret = -1;
	m_COperate.FuncConvert(m_deviceName,"WCDMAMeasResult",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到WCDMAMeasResult对应的驱动信息");
	}

	int ret1=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet14 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet14)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA,EVM,Rho,MagError,FreError,&ret,len,len2,len3,len4);
			CString strTemp = "";
			strTemp.Format("%s", EVM);
			AfxMessageBox(strTemp);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegGSMEevm(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"GSMEevm",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMEevm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegLTEEvm(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"LTEEvm",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到LTEEvm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegWCDMARho(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"WCDMARho",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到WCDMARho对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}



void CSpectrumdigModeSet::RegMeasTX(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"MeasTX",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMEevm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegModeSetupAG(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"ModeSetupAG",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMEevm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegModeSetupBG(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"ModeSetupBG",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMEevm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegModeSetupEDR(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"ModeSetupEDR",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMEevm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegModeSetupGDO(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"ModeSetupGDO",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMEevm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegWLanBTReadData(char VISA[], char ModeType[], char RmsEvm[], char FreErr[], char PhaErr[])
{
	m_COperate.FuncConvert(m_deviceName,"WLanBTReadData",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMEevm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet20 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet20)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA,ModeType,RmsEvm,FreErr,PhaErr,100,100,100);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}

void CSpectrumdigModeSet::RegMeasSetup5ms(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"MeasSetup5ms",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到GSMEevm对应的驱动信息");
	}

	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet16 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet16)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			lpFunc(VISA);
		}
	}
	else
	{
		throw string("找不到动态库函数");
	}
	FreeLibrary(hModule);
}