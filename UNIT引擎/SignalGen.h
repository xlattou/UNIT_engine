#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CSignalGen
{
public:
	/////////////////////////构造函数////////////////////////////////////////////////////
	CSignalGen(char* device,                                                      //设备名称
		ShareMemory &myshare                                                 //共享内存操作对象
		);

	void RegGetSN(char VISA[], char SN[], int16_t *ret, int32_t len);
	int16_t RegRFDigModeOutSet(char VISA[], char ModeStateOut[]);
	int16_t RegRFGenClose(char VISA[]);
	int16_t RegRFGenDigModeSet(char VISA[], char ModeStateArb[]);
	void RegRFGenInit(char VISA[], char ModeReset[]);
	int16_t RegRFGenOutSet(char VISA[], char ModeOutput[]);
	int16_t RegRFGenSelectDigWave(char VISA[], char WaveName[]);
	int16_t RegRFGenSet(char VISA[], char FreqHz[], char AmpDBm[]);


	~CSignalGen(void);                                                            //析构函数
private:
	char m_dllPath[255];                                                     //设备dll地址
	char m_funcName[100];                                                    //功能名
	char m_deviceName[100];                                                  //设备逻辑名
	ShareMemory m_CShare;                                                    //共享内存空间处理对象

	COperateFunc m_COperate;                                                 //操作函数对象
};