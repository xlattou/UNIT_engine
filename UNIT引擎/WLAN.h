#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CWLAN
{
public:
	/////////////////////////���캯��////////////////////////////////////////////////////
	CWLAN();
	CWLAN(char* device,                                                      //�豸����
		ShareMemory &myshare                                                 //�����ڴ��������
		);

	//
	int RegRFFreLev(int stateSet,double centerFre,char *VISA,char *CH); 
	//
	int RegParamSetting(char *VISA,char *centerFre,char *RF,char *VSA,char *ROUT,char *ModeType);
	int RegIQ3140RFFreLevVsg(int stateSet,double centerFre,double level,char *VISA,char *RF,char *VSG,char *ROUT); //ѡ��״̬: 0:��ʼ��
	                                                                                                               //1����Ƶ�ź�Դ
		                                                                                                           //2��GSM
			                                                                                                       //3��WCDMA
																												   //4��CDMA2000
																												   //5��TD-CDMA
																												   //6��LTE

	int RegIQ3140RFFreLevVsa(char *Idn,char *RetLevel,char *RhoPhase,char *FreErr,char *EvmErr,char *MagErr);  //����Ƶ�ʣ���ַ��ͨ����
	//�ű�����0��ʾ��λ������1��ʾ�򿪲���Wlan����          

	int RegIQ2200RFFreLevVsg(int ModeType,char *VISA, /*char *ModeType, */char *RF, char *ROUT, char *VSG, char *Level, char *Fre); 

	void RegIQ2200RFFreLevVsa(char *IDN, char *retLevel, char *Ref1, char *Ref2, char *Ref3, char *Ref4);

	~CWLAN(void);                                                            //��������
private:
	char m_CenterFre[50];
	char m_VisaAddr[200];
	char m_RF[10];
	char m_VSA[10];
	char m_ROUT[10];
	char m_ModeType[20];
	char m_dllPath[255];                                                     //�豸dll��ַ
	char m_funcName[100];                                                    //������
	char m_deviceName[100];                                                  //�豸�߼���
	ShareMemory m_CShare;                                                    //�����ڴ�ռ䴦�����

	COperateFunc m_COperate;                                                 //������������
};