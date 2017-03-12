#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CSignalGen
{
public:
	/////////////////////////���캯��////////////////////////////////////////////////////
	CSignalGen(char* device,                                                      //�豸����
		ShareMemory &myshare                                                 //�����ڴ��������
		);

	void RegGetSN(char VISA[], char SN[], int16_t *ret, int32_t len);
	int16_t RegRFDigModeOutSet(char VISA[], char ModeStateOut[]);
	int16_t RegRFGenClose(char VISA[]);
	int16_t RegRFGenDigModeSet(char VISA[], char ModeStateArb[]);
	void RegRFGenInit(char VISA[], char ModeReset[]);
	int16_t RegRFGenOutSet(char VISA[], char ModeOutput[]);
	int16_t RegRFGenSelectDigWave(char VISA[], char WaveName[]);
	int16_t RegRFGenSet(char VISA[], char FreqHz[], char AmpDBm[]);


	~CSignalGen(void);                                                            //��������
private:
	char m_dllPath[255];                                                     //�豸dll��ַ
	char m_funcName[100];                                                    //������
	char m_deviceName[100];                                                  //�豸�߼���
	ShareMemory m_CShare;                                                    //�����ڴ�ռ䴦�����

	COperateFunc m_COperate;                                                 //������������
};