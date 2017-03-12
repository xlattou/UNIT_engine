#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CSpectrumdigModeSet
{
public:
//	/////////////////////////构造函数////////////////////////////////////////////////////
	CSpectrumdigModeSet(char* device,                                                      //设备名称
		ShareMemory &myshare                                                 //共享内存操作对象
		);
//
	int RegSpecModeSet(char VISA[], char ModeName[]);
	int16_t RegLTESetULink(char VISA[]);
	int16_t RegLTESetB10M(char VISA[]);
	int16_t RegWCDMAradioMS(char VISA[]);
	void RegGSMMeasResult(char VISA[], char PhaseErr[], char FreqErr[], char EVM[]);
	void RegLTEMeasResult(char VISA[], char EVM[], char FreError[]);
	void RegCDMA2000MeasResult(char VISA[], char EVM[], char Rho[],char FreError[]);
	void RegWCDMAMeasResult(char VISA[], char EVM[], char Rho[],char MagError[], char FreError[]);
	void RegGSMEevm(char VISA[]);
	void RegLTEEvm(char VISA[]);
	void RegWCDMARho(char VISA[]);

	void RegMeasTX(char VISA[]);
	void RegModeSetupAG(char VISA[]);
	void RegModeSetupBG(char VISA[]);
	void RegModeSetupEDR(char VISA[]);
	void RegModeSetupGDO(char VISA[]);
	void RegWLanBTReadData(char VISA[], char ModeType[], char RmsEvm[], char FreErr[], char PhaErr[]);
	void RegMeasSetup5ms(char VISA[]);

	~CSpectrumdigModeSet(void);                                                            //析构函数
private:
	char m_dllPath[255];                                                     //设备dll地址
	char m_funcName[100];                                                    //功能名
	char m_deviceName[100];                                                  //设备逻辑名
	ShareMemory m_CShare;                                                    //共享内存空间处理对象
//
	COperateFunc m_COperate;                                                 //操作函数对象
};