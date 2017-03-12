#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CSpectrum
{
public:
	///////////////////���캯��///////////////////////////////////////////////////////
	CSpectrum(char* device,ShareMemory &myshare);
	int SpecInit(BOOL isReset);  //Ƶ�׷����ǳ�ʼ��
	int SpecClose(int intSerial); //�豸�ر�
	int SpecRefLevelConfig(char* level);  //�ο���ƽ����
	int SpecFreqConfig(char* freq); //����Ƶ������
	int SpecSpanConfig(char* span); //ɨƵ��������
	int SpecSweepConfig(char* isSingle,char* isAutoTime,char* SweepTime); //ɨ��ʱ������
	int SpecBandWidthConfig(char* RBW, char* VBW,char* AverageTimes); //�ֱ������Ƶ��������
	int SpecActiveMarker(char* markerNumber,char* activeMode,char* position); //��Ǽ��λ������
	int SpecMoveMarker(char* markerNumber,char* position); //�ƶ�Marker��ָ����λ��
	int SpecGetMarkerLevel(char* markNumber,char* level); //��ȡMarker���ƽ
	int SpecGetMarkerFreq(char* markNumber,char* freq); //��ȡMarker��Ƶ��
	int SpecGetWave(char* waveData);  //��ȡƵ���ǲ���

    int SpecAttenConfig(char* isAuto,char* attenuation);  //����˥������
	int SpecDetectorConfig(char* mode);   //�첨ģʽ����
	int SpecTraceModeConfig(char* traceNumber,char* mode);  //ɨ��ģʽ����
	int SpecAllMarkerOff();  //����Marker��
	int SpecAllDeltaMarkerOff(); //�ر�Marker����DeltaMarkerģʽ
	int SpecDeltaMarkerConfig(char* markerNumber,char* mode, char* position);  //DeltaMarker����
	int SpecSetLimitLine(char* mode,char* lineNumber,char* isDisplay, char* position); //���ޱ߽�����
	int SpecReadFileFromIns(char* source,char* dest);  
	int SpecHardcopyToFile(char*deviceNumber,char* fileName,char* dataFormat,char* pageOrientation);
    int SpecAmpConfig(char*isLog,char* LogScale,char* unit);
	int SpecMarkerCount(char* markerNumber, char* isCount, char* gateTime);
	int SpecGetMarkerCount(char* markerNumber, char* freq);
	int SpecInputCoupleSet(char* isDC);
	int ReceiverPreAmpConfig(char* isOn);
	int SpecContinuous(char* continMode);


	/////////////////////////////////���ܺ���/////////////////////////////////////////
	int SpecRBWTest(char* waveData,int NdB,char* RBW); //����ֱ������� waveData=���벨���ַ������� NdB=3 or 6 dB ;RBW=����õ���RBWֵ
    int SpecRBWTestM(char* waveData,int NdB,char* RBW,char* marker1,char*marker2);

	~CSpectrum(void);

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
