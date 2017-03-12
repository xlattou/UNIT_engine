#pragma once

#include "HidUart.h"


//ѡ�����ñ��������
#define SW( x )		( x << 4 )	    // 0 < x < 11  ����λ��
#define SL( x )		( x )		// 0 < x < 4   SELECT����
#define MN( x )		( x << 4 )		// 0 < x < 9   MENUλ��
#define FX( x )		( x )			// 0 < x < 4   F1,F2,F3,F4�еĵ�x����

class CMultimeter
{
public:
	CMultimeter(char* device, //�豸����
		ShareMemory &myshare //�����ڴ��������
		);
	~CMultimeter(void);

private:
	char m_com[100];       //�豸�����ַ
	char m_dllPath[255];   //�豸dll��ַ
	char m_funcName[100];  //������
	char m_channel[100];   //ͨ��
	char m_deviceName[100];  //�豸�߼� ��
	char m_deviceHandle[100];  //�豸������
	DWORD sequense[100];
	
	HMODULE m_InitModule;     //��ʼ��dll���
	ShareMemory m_CShare;     //�����ڴ�ռ䴦�����
	COperateFunc m_COperate;  //������������
	CHidUart m_CHidUart;      //���ڲ���

public:

	int MultiQueryResult(char* model, char* serialNum);          //��ȡ�ͺź����к�
	int MultiNumbers(char* hidnumber,char* multinumber);         //���Hid���������ñ�����
	int MultiConnect(char* number);                              //������������ñ�
	int MultiDisconnect(char* number);                           //�Ͽ��������ñ�
	int MultiRangeSet(char* range);                              //��������
	int MultiReadResult(char* value, char* unit,char* funcSet,char* range);   //��ȡ���ֵ����λ���������á�����
	int MultiMeasFuncSet(char* sW, char* sL, char* mN, char* fX);             //��������
	int MultiInit(char* isReset);                                             //��ʼ��
	int MultiClose(int intSerial);                                            //�ر�
	int MultiDeviceNumbers(std::vector<CString> & deviceList);
	int MultiReadResultData(float& resultvalue);
	int MultiReadSampleResult(char* count, char* intervalTime, char* limitValue, char* result);
	int MultiReadSampleResult_M(char* numbers,char* count, char* intervalTime, char* limitValue, char* result);

	int MultiInvalidValue(char* numbers,char* result);
	//int MultiMeasureSet(char* numbers, char* funcSet, char* rangeSet);
	int MultiRemoveMisuse();
};
