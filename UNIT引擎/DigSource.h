#pragma once

#include"ShareMemory.h"
#include "OperateFunc.h"

class CDigSource
{
public:
	CDigSource(char* device, //设备名称
		ShareMemory &myshare //共享内存操作对象
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
