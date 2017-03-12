#include "stdafx.h"
#include "WLAN.h"

CWLAN::CWLAN(char* device,ShareMemory &myshare):m_CShare(myshare)
{
	strcpy(m_deviceName,device);
}

CWLAN::CWLAN()
{

}

CWLAN::~CWLAN(void)
{

}

int CWLAN:: RegRFFreLev(int stateSet,double centerFre,char *VISA,char *CH)
{
	////////////////////////////////////////////////////////
	//char VISA[] = "TCPIP0::192.168.100.254::hislip0::INSTR";
	//char CH[] = "1";
	double Fre = centerFre;
	double Level = -6 ;
	char StateOn[] = "ON";
	char StateOff[] = "OFF";
	int16_t *ret0 = 0;
	////////////////////////////////////////////////////////
	m_COperate.FuncConvert(m_deviceName,"RFFreLev",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet8 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet8)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			if (stateSet == 0)
			{
				ret=lpFunc(VISA,CH,Fre,Level,StateOff,ret0);
			}
			if (stateSet == 1)
			{
				ret=lpFunc(VISA,CH,Fre,Level,StateOn,ret0);
			}
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

//IQ3140
int CWLAN:: RegIQ3140RFFreLevVsg(int stateSet,double centerFre,double level,char *VISA,char *RF,char *VSG,char *ROUT)
{
	m_COperate.FuncConvert(m_deviceName,"IQ3140RFLevSet",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet9 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet9)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			switch(stateSet)
			{
				case 0:
					{
						char State[] = "OFF";
						ret=lpFunc(NULL,RF,VSG,State,level,centerFre,NULL,ROUT,VISA);
						break;
					}
				case 1:
					{
						char State[] = "ON";
						ret=lpFunc(NULL,RF,VSG,State,level,centerFre,NULL,ROUT,VISA);
						break;
					}
				case 2:
					{
						char State[] = "GSM";
						char ModeTemplate[] = "/GSM/GSM_UL_GMSK.iqvsg";
						char ModeState[] = "ON";
						ret=lpFunc(ModeTemplate,RF,VSG,State,level,centerFre,ModeState,ROUT,VISA);
						break;
					}
				case 3:
					{
						char State[] = "WCDMA";
						char ModeTemplate[] = "/WCDMA/WCDMA_UL.iqvsg";
						char ModeState[] = "ON";
						ret=lpFunc(ModeTemplate,RF,VSG,State,level,centerFre,ModeState,ROUT,VISA);
						break;
					}
				case 4:
					{
						char State[] = "CDMA2000";
						char ModeTemplate[] = "/CDMA2K/CDMA2K_DL_Channel_1175.iqvsg";
						char ModeState[] = "ON";
						ret=lpFunc(ModeTemplate,RF,VSG,State,level,centerFre,ModeState,ROUT,VISA);
						break;
					}
				case 5:
					{
						char State[] = "TD-CDMA";
						char ModeTemplate[] = "/TDSCDMA/TDSCDMA_UL.iqvsg";
						char ModeState[] = "ON";
						ret=lpFunc(ModeTemplate,RF,VSG,State,level,centerFre,ModeState,ROUT,VISA);
						break;
					}
				case 6:
					{
						char State[] = "LTE";
						char ModeTemplate[] = "/LTE/LTE_FDD_UL_10MHZ_50RB_QPSK_DUT.iqvsg";
						char ModeState[] = "ON";
						ret=lpFunc(ModeTemplate,RF,VSG,State,level,centerFre,ModeState,ROUT,VISA);
						break;
					}
				default:
					break;
			
			}		
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int CWLAN:: RegParamSetting(char *VISA,char *centerFre,char *RF,char *VSA,char *ROUT,char *ModeType)
{
	strcpy(m_CenterFre,centerFre);  
	strcpy(m_VisaAddr,VISA);
	strcpy(m_RF,RF);
	strcpy(m_VSA,VSA);
	strcpy(m_ROUT,ROUT);
	strcpy(m_ModeType,ModeType);
	return 0;
}

int CWLAN:: RegIQ3140RFFreLevVsa(char *Idn,char *RetLevel,char *RhoPhase,char *FreErr,char *EvmErr,char *MagErr)
{
	m_COperate.FuncConvert(m_deviceName,"IQ3140RFLevRec",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet17 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet17)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{

			lpFunc(m_VisaAddr,m_CenterFre,m_ModeType,m_VSA,m_ROUT,m_RF,Idn,RetLevel,RhoPhase,FreErr,EvmErr,MagErr,100,100,100,100,100,100);
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int CWLAN:: RegIQ2200RFFreLevVsg(int ModeType,char *VISA, /*char *ModeType,*/ char *RF, char *ROUT, char *VSG, char *Level, char *Fre)
{
	m_COperate.FuncConvert(m_deviceName,"IQ2200RFFreLevVsg",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet18 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet18)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{

			//lpFunc(VISA,ModeType,RF,ROUT,VSG,Level,Fre);
			switch(ModeType)
			{
			case 0:
				{
					char State[] = "OFF";
					ret=lpFunc(VISA,State,RF,ROUT,VSG,Level,Fre);
					break;
				}
			case 1:
				{
					char State[] = "CW";
					ret=lpFunc(VISA,State,RF,ROUT,VSG,Level,Fre);
					break;
				}
			case 2:
				{
					char State[] = "WIFIOFDM";
					ret=lpFunc(VISA,State,RF,ROUT,VSG,Level,Fre);
					break;
				}
			case 3:
				{
					char State[] = "WIFIGR";
					ret=lpFunc(VISA,State,RF,ROUT,VSG,Level,Fre);
					break;
				}
			case 4:
				{
					char State[] = "WIFIRC";
					ret=lpFunc(VISA,State,RF,ROUT,VSG,Level,Fre);
					break;
				}
			case 5:
				{
					char State[] = "BT";
					ret=lpFunc(VISA,State,RF,ROUT,VSG,Level,Fre);
					break;
				}
			default:
				break;
			}		
			
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

void CWLAN:: RegIQ2200RFFreLevVsa(char *IDN, char *retLevel, char *Ref1, char *Ref2, char *Ref3, char *Ref4)
{
	//char *VISA, char *Fre, char *ModeType,char *VSA, char *ROUT, char *RF, 
	m_COperate.FuncConvert(m_deviceName,"IQ2200RFFreLevVsa",m_dllPath,m_funcName);//从TestConfig文件夹的ini文件中读取设备逻辑名称,功能逻辑名称,dll文件地址,函数名称
	if(((string)m_funcName).empty())
	{
		throw string("找不到DigMeterReadData对应的驱动信息");
	}
	CString strTemp = "";
	strTemp.Format("%s",m_dllPath);
	AfxMessageBox(strTemp);
	strTemp.Format("%s",m_funcName);
	AfxMessageBox(strTemp);
	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
	MySet19 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet19)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			AfxMessageBox("vsa开始调用接口函数");
			lpFunc(m_VisaAddr,m_CenterFre,m_ModeType,m_VSA,m_ROUT,m_RF,IDN,retLevel,Ref1,Ref2,Ref3,Ref4,100,100,100,100,100,100);
			strTemp.Format("%s",Ref1);
			AfxMessageBox(strTemp);
			strTemp.Format("%s",Ref2);
			AfxMessageBox(strTemp);
			strTemp.Format("%s",Ref3);
			AfxMessageBox(strTemp);
			strTemp.Format("%s",Ref4);
			AfxMessageBox(strTemp);
		}
		else
		{
			throw string("找不到动态库函数");
		}
		FreeLibrary(hModule);
	}
}