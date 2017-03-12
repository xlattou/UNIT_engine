#pragma once

#include "HidUart.h"


//选择万用表测量功能
#define SW( x )		( x << 4 )	    // 0 < x < 11  刀盘位置
#define SL( x )		( x )		// 0 < x < 4   SELECT次序
#define MN( x )		( x << 4 )		// 0 < x < 9   MENU位置
#define FX( x )		( x )			// 0 < x < 4   F1,F2,F3,F4中的第x个键

class CMultimeter
{
public:
	CMultimeter(char* device, //设备名称
		ShareMemory &myshare //共享内存操作对象
		);
	~CMultimeter(void);

private:
	char m_com[100];       //设备物理地址
	char m_dllPath[255];   //设备dll地址
	char m_funcName[100];  //功能名
	char m_channel[100];   //通道
	char m_deviceName[100];  //设备逻辑 名
	char m_deviceHandle[100];  //设备物理句柄
	DWORD sequense[100];
	
	HMODULE m_InitModule;     //初始化dll句柄
	ShareMemory m_CShare;     //共享内存空间处理对象
	COperateFunc m_COperate;  //操作函数对象
	CHidUart m_CHidUart;      //串口操作

public:

	int MultiQueryResult(char* model, char* serialNum);          //获取型号和序列号
	int MultiNumbers(char* hidnumber,char* multinumber);         //检查Hid数量和万用表数量
	int MultiConnect(char* number);                              //按序号连接万用表
	int MultiDisconnect(char* number);                           //断开连接万用表
	int MultiRangeSet(char* range);                              //设置量程
	int MultiReadResult(char* value, char* unit,char* funcSet,char* range);   //读取结果值、单位、功能设置、量程
	int MultiMeasFuncSet(char* sW, char* sL, char* mN, char* fX);             //功能设置
	int MultiInit(char* isReset);                                             //初始化
	int MultiClose(int intSerial);                                            //关闭
	int MultiDeviceNumbers(std::vector<CString> & deviceList);
	int MultiReadResultData(float& resultvalue);
	int MultiReadSampleResult(char* count, char* intervalTime, char* limitValue, char* result);
	int MultiReadSampleResult_M(char* numbers,char* count, char* intervalTime, char* limitValue, char* result);

	int MultiInvalidValue(char* numbers,char* result);
	//int MultiMeasureSet(char* numbers, char* funcSet, char* rangeSet);
	int MultiRemoveMisuse();
};
