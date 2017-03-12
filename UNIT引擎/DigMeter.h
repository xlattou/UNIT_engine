#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CDigMeter
{
public:
	/////////////////////////���캯��////////////////////////////////////////////////////
	CDigMeter(char* device, //�豸����
		ShareMemory &myshare //�����ڴ��������
		);
///////////////////////////�������ñ�������///////////////////////////////////////////////
	int DigMeterInit(char* isReset);  //�������ñ��ʼ��
	int DigMeterClose(int intSerial); //�豸�ر�

	int DigMeterConfig(char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution); //��������
	int DigMeterAutoZero(char* Func); //�Զ���0
	int DigMeterCal(char* RangeValue);//�Զ�У׼
    int DigMeterCalSave();//У׼���ݱ���
	int DigMeterConfig_M(char* Chan,char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution); //��������,��ͨ��

	int DigMeterRead(char* data); //�����ȡ


	int DigMeterRead_M(char* Chan,char* data); //�����ȡ����ͨ��
    int DigMeterReadData(char* Chan,char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution,char* value); //34970A��ȡ������Ҫ���ã�ֱ�Ӷ�ȡ
	//��������
	~CDigMeter(void);
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
