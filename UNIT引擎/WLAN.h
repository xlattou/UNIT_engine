#pragma once
#include"ShareMemory.h"
#include "OperateFunc.h"

class CWLAN
{
public:
	/////////////////////////构造函数////////////////////////////////////////////////////
	CWLAN();
	CWLAN(char* device,                                                      //设备名称
		ShareMemory &myshare                                                 //共享内存操作对象
		);

	//
	int RegRFFreLev(int stateSet,double centerFre,char *VISA,char *CH); 
	//
	int RegParamSetting(char *VISA,char *centerFre,char *RF,char *VSA,char *ROUT,char *ModeType);
	int RegIQ3140RFFreLevVsg(int stateSet,double centerFre,double level,char *VISA,char *RF,char *VSG,char *ROUT); //选择状态: 0:初始化
	                                                                                                               //1：射频信号源
		                                                                                                           //2：GSM
			                                                                                                       //3：WCDMA
																												   //4：CDMA2000
																												   //5：TD-CDMA
																												   //6：LTE

	int RegIQ3140RFFreLevVsa(char *Idn,char *RetLevel,char *RhoPhase,char *FreErr,char *EvmErr,char *MagErr);  //中心频率；地址；通道数
	//脚本传入0表示复位，传入1表示打开参数Wlan设置          

	int RegIQ2200RFFreLevVsg(int ModeType,char *VISA, /*char *ModeType, */char *RF, char *ROUT, char *VSG, char *Level, char *Fre); 

	void RegIQ2200RFFreLevVsa(char *IDN, char *retLevel, char *Ref1, char *Ref2, char *Ref3, char *Ref4);

	~CWLAN(void);                                                            //析构函数
private:
	char m_CenterFre[50];
	char m_VisaAddr[200];
	char m_RF[10];
	char m_VSA[10];
	char m_ROUT[10];
	char m_ModeType[20];
	char m_dllPath[255];                                                     //设备dll地址
	char m_funcName[100];                                                    //功能名
	char m_deviceName[100];                                                  //设备逻辑名
	ShareMemory m_CShare;                                                    //共享内存空间处理对象

	COperateFunc m_COperate;                                                 //操作函数对象
};