#pragma once

#include"ShareMemory.h"
#include "OperateFunc.h"

class Switch
{
public:
	Switch(char* device,ShareMemory &myShare);
	int SwitchSet(char* Mark);
	int SwitchTemperature(char* temperature);
	~Switch(void);
private:

	char com[255];
	char dllPath[255];
	char funcName[255];
	char channel[255];
	char deviceName[100];
	COperateFunc myOperate;
	ShareMemory m_CShare;

};
