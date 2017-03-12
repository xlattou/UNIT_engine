typedef int (__stdcall * MyInit)(char* com,char* isReset,char* handleOut,int num);
typedef int (__stdcall * MySet)(char* handleIn,char* freq,char* span,char* rbw,char* refLevel); //Ƶ����
typedef int (__stdcall * MyPowerTest)(char* handleIn,char* result,int num);

typedef int (__stdcall * MySet1)(char* handleIn,char* freq,char* level);
typedef int (__stdcall * MySet2)(char* handleIn,char* channel,char* freq1,char* level1,char* freq2,char* level2);
typedef int (__stdcall * MySet3)(char* handleIn,char* channel,char* freq1,char* level1,char* freq2,char* level2,char* freq3,char* level3);
typedef int (__stdcall * MySet4)(char* handleIn,char* var);
typedef int (__stdcall * MySet5)(char* handleIn,char*channel,char* freq,char* level);
typedef int (__stdcall * MySet6)(char*com,char* function, char* value, char* unit, char* freq,char* unit_Freq,char* currentPort);
typedef int (__stdcall * MySet7)(char*com,char* chan, char* func, char* isAutorange, char* manuRange,char* unit,char* manuResolution,char* value,int len);
typedef int (__stdcall * MySet8)(char VISA[], char CH[], double Fre, double Level, char State[], int16_t *ret);
typedef int (__stdcall * MySet9)(char ModeTemplate[], char RF[], char VSG[], char State[], double Level, double Fre, char ModeState[], char ROUT[], char VISAaddr[]);
typedef int (__stdcall * MySet10)(char* handleIn);
typedef void (__stdcall * MySet11)(char *VISA, char *PhaseErr, char *FreqErr, char *EVM, int16_t *ret, int32_t len, int32_t len2, int32_t len3);
typedef void (__stdcall * MySet12)(char VISA[], char EVM[], char FreError[],int16_t *ret, int32_t len, int32_t len2);
typedef void (__stdcall * MySet13)(char VISA[], char EVM[], char Rho[],char FreError[], int16_t *ret, int32_t len, int32_t len2, int32_t len3);
typedef void (__stdcall * MySet14)(char VISA[], char EVM[], char Rho[],char MagError[], char FreError[], int16_t *ret, int32_t len, int32_t len2, int32_t len3, int32_t len4);
typedef int (__stdcall * MySet15)(char VISA[], char SN[], int16_t *ret, int32_t len);
typedef void (__stdcall * MySet16)(char* handleIn);
typedef void (__stdcall * MySet17)(char VISAaddr[], char Fre[], char ModeType[], char VSA[], char ROUT[], char RF[], char IDN[], char retLevel[], 
	char Ref1[], char Ref2[], char Ref3[], char Ref4[], 
	int32_t len, int32_t len2, int32_t len3, int32_t len4, int32_t len5, 
	int32_t len6);
typedef int (__stdcall * MySet18)(char VISA[], char ModeType[], char RF[], char ROUT[], char VSG[], char Level[], char Fre[]);
typedef void (__stdcall * MySet19)(char VISA[], char Fre[], char ModeType[], char VSA[], char ROUT[], char RF[], char IDN[], char retLevel[], char Ref1[], 
	char Ref2[], char Ref3[], char Ref4[], int32_t len, int32_t len2, 
	int32_t len3, int32_t len4, int32_t len5, int32_t len6);
typedef void (__stdcall * MySet20)(char VISA[], char ModeType[], char RmsEvm[], char FreErr[], char PhaErr[], int32_t len, int32_t len2, int32_t len3);
typedef int (__stdcall * MyControl)(char* handleIn);
typedef int (__stdcall * MyTest)(char* handleIn,char* channnel,char* result,int num);
typedef int (__stdcall * HidUart1)(unsigned long* numDevice,unsigned short vid,unsigned short pid);//GetNumDevices
typedef int (__stdcall * HidUart2)(unsigned long DeviceNum,unsigned short vid,unsigned short pid,char* deviceString,DWORD options);//GetString
typedef int (__stdcall * HidUart3)(void** Device,unsigned long DeviceNum,unsigned short vid,unsigned short pid);//DeviceOpen
typedef int (__stdcall * HidUart4)(void* Device);//DeviceClose
typedef int (__stdcall * HidUart5)(void* Device,unsigned long baudRate,unsigned char dataBits,unsigned char parity,unsigned char stopBits,unsigned char flowControl);//SetUartConfig
typedef int (__stdcall * HidUart6)(void* Device,unsigned long* baudRate,unsigned char* dataBits,unsigned char* parity,unsigned char* stopBits,unsigned char* flowControl);//GetUartConfig
typedef int (__stdcall * HidUart7)(void* Device,unsigned long readTimeout,unsigned long writeTimeout);//SetTimeouts
typedef int (__stdcall * HidUart8)(void* Device,unsigned char* buffer,unsigned long numBytesToWrite,unsigned long* numBytesWritten);//DeviceWrite
typedef int (__stdcall * HidUart9)(void* Device,unsigned char* buffer,unsigned long numBytesToRead,unsigned long* numBytesRead);//DeviceRead

#pragma once
#include "MessageDecide.h"
#include "MessageInput.h"
#include "Frm_Message.h"





class COperateFunc
{
public:
	COperateFunc(void);
	/**********************��λ�豸����*********************************/
	int FuncConvert(char* deviceName,char* logicalName,char* com, char* channel,char* dllPath,char* funcName);  //����ת������,���չ��ܵ��߼����ƴ�ϵͳ�����ļ��ж�ȡ�����ַ��ͨ����dll�ļ���ַ�ͺ���������Ϣ
	  /************************************************************************/
	int COperateFunc::FuncConvert(char* deviceName,char* logicalName,char* dllPath,char* funcName);

	/*��ָ����ӳ���ַ����а����߼����ƶ�ȡ��Ӧ������*/
	int GetFunc(char* inputString,char* LogicName,char* MyString);  
	int StringSplit(char* inputString,char* regular,char* X,char* Y);
	void strToChar(string s,char* result);
	double stringToDouble(string s);
	int stringToInt(string s);
	int GetRunStatus();
	int WriteHandles(char* deviceName,char* handle);
	int ReadHandles(char* deviceName,char* handle);
	int WriteHandles(char* deviceName,char* key,char* handle);
	int ReadHandles(char* deviceName,char* key,char* handle);

	//int ShowMessage(char* message);
	int ShowMessage(char* message,char* flag);
	

	int WriteStatusCache(char* cacheName,char* value);  //д״̬���棬cacheName ����������ƣ�Value �����ַ���
	int ReadStatusCache(char* cacheName,char* value,char* status); //��״̬���棬cacheName ����������ƣ�value �����ַ�����status ״ֵ̬ 1=��д 0=δд
	int WriteStatusCache_M(char* cacheName,char* value1,char* value2);
	int ReadStatusCache_M(char* cacheName, char* value1, char* value2);
	int InputMessage(char* key,char* message,char* unit); //�����Ի������������key��ֵ��message��ʾ�������ߵ���ʾ��Ϣ��unit��������ĵ�λ������ʾ
	////////////////����///////////////////////////////
	static CString m_strTestConfig;
	Frm_Message *m_Pfrm_Message;



	~COperateFunc(void);
	int ResultDecide(char* result);
	int ReadSampleSet(char* item, char* waittime, char* count, char* interval);
	int ResultCorrection(char* resultStr,char* digit,char* offset,char* result);
	int ChannelCalibration_M(char* resultStr, char* mode, char* result);
};
