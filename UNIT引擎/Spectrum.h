#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CSpectrum
{
public:
	///////////////////构造函数///////////////////////////////////////////////////////
	CSpectrum(char* device,ShareMemory &myshare);
	int SpecInit(BOOL isReset);  //频谱分析仪初始化
	int SpecClose(int intSerial); //设备关闭
	int SpecRefLevelConfig(char* level);  //参考电平设置
	int SpecFreqConfig(char* freq); //中心频率设置
	int SpecSpanConfig(char* span); //扫频带宽设置
	int SpecSweepConfig(char* isSingle,char* isAutoTime,char* SweepTime); //扫描时间设置
	int SpecBandWidthConfig(char* RBW, char* VBW,char* AverageTimes); //分辨带宽、视频带宽设置
	int SpecActiveMarker(char* markerNumber,char* activeMode,char* position); //标记激活及位置设置
	int SpecMoveMarker(char* markerNumber,char* position); //移动Marker到指定的位置
	int SpecGetMarkerLevel(char* markNumber,char* level); //读取Marker点电平
	int SpecGetMarkerFreq(char* markNumber,char* freq); //读取Marker点频率
	int SpecGetWave(char* waveData);  //读取频谱仪波形

    int SpecAttenConfig(char* isAuto,char* attenuation);  //输入衰减设置
	int SpecDetectorConfig(char* mode);   //检波模式配置
	int SpecTraceModeConfig(char* traceNumber,char* mode);  //扫描模式配置
	int SpecAllMarkerOff();  //所有Marker关
	int SpecAllDeltaMarkerOff(); //关闭Marker所有DeltaMarker模式
	int SpecDeltaMarkerConfig(char* markerNumber,char* mode, char* position);  //DeltaMarker配置
	int SpecSetLimitLine(char* mode,char* lineNumber,char* isDisplay, char* position); //界限边界设置
	int SpecReadFileFromIns(char* source,char* dest);  
	int SpecHardcopyToFile(char*deviceNumber,char* fileName,char* dataFormat,char* pageOrientation);
    int SpecAmpConfig(char*isLog,char* LogScale,char* unit);
	int SpecMarkerCount(char* markerNumber, char* isCount, char* gateTime);
	int SpecGetMarkerCount(char* markerNumber, char* freq);
	int SpecInputCoupleSet(char* isDC);
	int ReceiverPreAmpConfig(char* isOn);
	int SpecContinuous(char* continMode);


	/////////////////////////////////功能函数/////////////////////////////////////////
	int SpecRBWTest(char* waveData,int NdB,char* RBW); //计算分辨力带宽 waveData=输入波形字符串数据 NdB=3 or 6 dB ;RBW=计算得到的RBW值
    int SpecRBWTestM(char* waveData,int NdB,char* RBW,char* marker1,char*marker2);

	~CSpectrum(void);

private:
	char m_com[100];       //设备物理地址
	char m_dllPath[255];   //设备dll地址
	char m_funcName[100];  //功能名
	char m_channel[100];   //通道
	char m_deviceName[100];  //设备逻辑 名
	char m_deviceHandle[100];  //设备物理句柄
	HMODULE m_InitModule; //初始化dll句柄
	ShareMemory m_CShare;     //共享内存空间处理对象
	COperateFunc m_COperate;  //操作函数对象
};
