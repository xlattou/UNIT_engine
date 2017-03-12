#include "stdafx.h"
#include "DigMeter.h"

CDigMeter::CDigMeter(char* device,ShareMemory &myshare):m_CShare(myshare)
{
	strcpy(m_deviceName,device);
}

CDigMeter::~CDigMeter(void)
{
}

int CDigMeter::DigMeterInit(char* isReset)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("1...");
	m_COperate.FuncConvert(m_deviceName,"DigMeterInit",m_com,m_channel,m_dllPath,m_funcName);//��ȡ����������dll������
	//	m_CShare.WriteToSharedMemory("2...");
	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //��ȡ�豸״̬
	string temp_s(status);
	//	m_CShare.WriteToSharedMemory("3...");
	if(temp_s!="Open")
	{
		//m_CShare.WriteToSharedMemory("�������ñ��ʼ��...");
		if(((string)m_funcName).empty())
		{
			throw string("�Ҳ���DigMeterInit��Ӧ��������Ϣ");
		}
		m_InitModule=LoadLibrary(m_dllPath);//����dll
		MyInit lpFunc=NULL;
		if(m_InitModule)
		{
			lpFunc=(MyInit)GetProcAddress(m_InitModule,m_funcName);
			if(lpFunc)
			{
				ret=lpFunc(m_com,isReset?"1":"0",m_deviceHandle,50);
			}
			else
			{
				if(!FreeLibrary(m_InitModule))
					throw string("ж�ض�̬���ӿ�ʧ��");
				throw string("�Ҳ�����ʼ������");
			}
		}
		else
		{
			throw string("�����������ñ��ʼ�������ʧ��");
		}
		if(ret==0)
		{
			m_CShare.WriteToSharedMemory("�������ñ��ʼ�����");
			int isWrite1=m_COperate.WriteHandles(m_com,"DeviceOutHandle",m_deviceHandle);  //д���豸��ַ
			int isWrite2=m_COperate.WriteHandles(m_com,"DeviceStatus","Open"); //д���豸״̬
			char hModule[20];
			sprintf_s(hModule,20,"%d",(int)(m_InitModule));
			m_COperate.WriteHandles(m_com,"InitDllHandle",hModule); //д���ʼ��dll���
			if((isWrite2|isWrite2)==0)
			{
				throw string("״̬д��ʧ��");
			}
		}
		else
		{
			m_CShare.WriteToSharedMemory("�������ñ��ʼ��ʧ��");
		}

	}
	else if(temp_s=="Open")
	{
		ret=0;
		m_COperate.ReadHandles(m_com,"DeviceOutHandle",m_deviceHandle);
		//	m_CShare.WriteToSharedMemory("4...");
		//m_CShare.WriteToSharedMemory("�������ñ�������");
	}
	return ret;
}

int CDigMeter::DigMeterClose(int intSerial)
{
	int ret=1;
	if(intSerial!=-1)
		return 0;
	m_COperate.FuncConvert(m_deviceName,"DigMeterClose",m_com,m_channel,m_dllPath,m_funcName);//��ȡ����������dll������

	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //��ȡ�豸״̬
	string temp_s(status);
	if(temp_s=="Close")
		return 0;
	char hInitModule[20];
	//m_CShare.WriteToSharedMemory("�������ñ�ر�");
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterClose��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyControl lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyControl)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle);
		}
		else
		{
			throw string("�Ҳ����������ñ�رպ���");
		}
		if(!FreeLibrary(hModule))
			throw string("ж�ض�̬���ӿ�ʧ��");
	//	if(ret==0)
	//	{
			m_COperate.ReadHandles(m_com,"InitDllHandle",hInitModule);  //��ȡ��ʼ��dll���
			m_InitModule=(HMODULE)(atoi(hInitModule));

			FreeLibrary(m_InitModule);
			//if(!FreeLibrary(m_InitModule))
			//	throw string("ж�س�ʼ����̬���ӿ�ʧ��");
			m_COperate.WriteHandles(m_com,"DeviceStatus","Close"); //д���豸״̬
		    m_CShare.WriteToSharedMemory("�������ñ������ѹر�");
	//	}
	//	else
	//	{
	  //  	m_CShare.WriteToSharedMemory("�ر��������ñ�����ʧ��");
	//	}

	}
	else
	{
		throw string("�����������ñ�رճ����ʧ��");
	}
	return ret;
}

int CDigMeter::DigMeterConfig(char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"DigMeterConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet2 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet2)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Func,isAutoRange,ManuRange,unit,ManuResolution);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ����������ñ����ú���");
		}
	}
	else
	{
		throw string("�����������ñ����ó����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}

int CDigMeter::DigMeterAutoZero(char* Func)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"DigMeterAutoZero",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterAutoZero��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Func);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ����������ñ���㺯��");
		}
	}
	else
	{
		throw string("�����������ñ��������ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}

int CDigMeter::DigMeterCal(char* RangeValue)
{
	char data[50];
	int ret=1;
	//m_CShare.WriteToSharedMemory("�������ñ�У׼");
	m_COperate.FuncConvert(m_deviceName,"DigMeterCal",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterCal��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,RangeValue,data,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ����������ñ�У׼����");
		}
	}
	else
	{
		throw string("�����������ñ�У׼�����ʧ��");
	}
	CString strData=data;
	if(strData.IsEmpty())
	{
    	m_CShare.WriteToSharedMemory("��ȫ�������ʧ��");
	}
	else if(atoi(data)==0)
	{
    	m_CShare.WriteToSharedMemory("У׼�ɹ�");
	}
	else
	{
    	m_CShare.WriteToSharedMemory("У׼ʧ��");
	}
	return 0;
}
int CDigMeter::DigMeterCalSave()
{
	//char data[50];
	int ret=1;
	//m_CShare.WriteToSharedMemory("�������ñ�У׼����");
	m_COperate.FuncConvert(m_deviceName,"DigMeterCalSave",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterCalSave��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyControl lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyControl)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ����������ñ�У׼���溯��");
		}
	}
	else
	{
		throw string("�����������ñ�У׼��������ʧ��");
	}
	return ret;
}
int CDigMeter::DigMeterRead(char* data)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("�������ñ��ȡ����");
	m_COperate.FuncConvert(m_deviceName,"DigMeterRead",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterRead��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyPowerTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyPowerTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,data,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ����������ñ���Ժ���");
		}
	}
	else
	{
		throw string("�����������ñ���Գ����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("���Խ��%s",data);
	return ret;
}

int CDigMeter::DigMeterConfig_M(char* Chan, char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"DigMeterConfig_M",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterConfig_M��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet6 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet6)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Chan,Func,isAutoRange,ManuRange,unit,ManuResolution);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ����������ñ����ú���");
		}
	}
	else
	{
		throw string("�����������ñ����ó����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}

int CDigMeter::DigMeterReadData(char* Chan,char* Func, char* isAutoRange, char* ManuRange,char* unit,char* ManuResolution,char* value)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"DigMeterReadData",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterReadData��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet7 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet7)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Chan,Func,isAutoRange,ManuRange,unit,ManuResolution,value,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ����������ñ��ȡ����");
		}
	}
	else
	{
		throw string("�����������ñ��ȡ�����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}
int CDigMeter::DigMeterRead_M(char* Chan, char* data)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("�������ñ��ȡ����");
	m_COperate.FuncConvert(m_deviceName,"DigMeterRead_M",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigMeterRead_M��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,Chan,data,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ����������ñ���Ժ���");
		}
	}
	else
	{
		throw string("�����������ñ���Գ����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("���Խ��%s",data);
	return ret;
}