#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CDigMeter
{
public:
	/////////////////////////构造函数////////////////////////////////////////////////////
	CDigMeter(char* device, //设备名称
		ShareMemory &myshare //共享内存操作对象
		);
///////////////////////////数字万用表函数定义///////////////////////////////////////////////
	int DigMeterInit(char* isReset);  //数字万用表初始化
	int DigMeterClose(int intSerial); //设备关闭

	int DigMeterConfig(char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution); //测试配置
	int DigMeterAutoZero(char* Func); //自动清0
	int DigMeterCal(char* RangeValue);//自动校准
    int DigMeterCalSave();//校准数据保存
	int DigMeterConfig_M(char* Chan,char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution); //测试配置,多通道

	int DigMeterRead(char* data); //结果读取


	int DigMeterRead_M(char* Chan,char* data); //结果读取，多通道
    int DigMeterReadData(char* Chan,char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution,char* value); //34970A读取，不需要设置，直接读取
	//析构函数
	~CDigMeter(void);
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
