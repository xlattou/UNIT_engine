#pragma once

#include"ShareMemory.h"
#include "OperateFunc.h"

class CDigSource
{
public:
	CDigSource(char* device, //�豸����
		ShareMemory &myshare //�����ڴ��������
		);

	~CDigSource(void);
	int DigSourceInit(char* isReset);
	int DigSourceClose(int intSerial);
	int DigSourceConfig(char* function, char* value, char* unit, char* freq,char* unit_Freq,char* currentPort);
	int DigSourceOutSet(char* isOutSet);
	int DigSourceOffset(char* offsetValue);
	int DigSourceWaveSet(char* wave,char* duty);
	int DigSourceReset(char* isReset);

private:
	char m_com[100];       //�豸�����ַ
	char m_dllPath[255];   //�豸dll��ַ
	char m_funcName[100];  //������
	char m_channel[100];   //ͨ��
	char m_deviceName[100];  //�豸�߼� ��
	char m_deviceHandle[100];  //�豸������
	HMODULE m_InitModule; //��ʼ��dll���
	ShareMemory m_CShare;     //�����ڴ�ռ䴦�����
	COperateFunc m_COperate;  //������������
};
