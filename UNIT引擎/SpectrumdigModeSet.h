#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CSpectrumdigModeSet
{
public:
//	/////////////////////////���캯��////////////////////////////////////////////////////
	CSpectrumdigModeSet(char* device,                                                      //�豸����
		ShareMemory &myshare                                                 //�����ڴ��������
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

	~CSpectrumdigModeSet(void);                                                            //��������
private:
	char m_dllPath[255];                                                     //�豸dll��ַ
	char m_funcName[100];                                                    //������
	char m_deviceName[100];                                                  //�豸�߼���
	ShareMemory m_CShare;                                                    //�����ڴ�ռ䴦�����
//
	COperateFunc m_COperate;                                                 //������������
};