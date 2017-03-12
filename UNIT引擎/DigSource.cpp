#include "stdafx.h"
#include "DigSource.h"

CDigSource::CDigSource(char* device,ShareMemory &myshare):m_CShare(myshare)
{
		strcpy(m_deviceName,device);
}

CDigSource::~CDigSource(void)
{
}

int CDigSource::DigSourceInit(char* isReset)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceInit",m_com,m_channel,m_dllPath,m_funcName);//��ȡ����������dll������
    
	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //��ȡ�豸״̬
	string temp_s(status);
	if(temp_s!="Open")
	{
		//m_CShare.WriteToSharedMemory("У׼Դ��ʼ��...");
		if(((string)m_funcName).empty())
		{
			throw string("�Ҳ���DigSourceInit��Ӧ��������Ϣ");
		}
		m_InitModule=LoadLibrary(_T(m_dllPath));//����dll
		
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
			throw string("����У׼Դ��ʼ�������ʧ��");
		}
		if(ret==0)
		{
			m_CShare.WriteToSharedMemory("У׼Դ��ʼ�����");
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
			m_CShare.WriteToSharedMemory("У׼Դ��ʼ��ʧ��");
		}

	}
	else if(temp_s=="Open")
	{
		ret=2;
		m_COperate.ReadHandles(m_com,"DeviceOutHandle",m_deviceHandle);
		//m_CShare.WriteToSharedMemory("У׼Դ����������");
	}
	return ret;
}

int CDigSource::DigSourceClose(int intSerial)
{
	int ret=1;
	if(intSerial!=-1)
		return 0;
	m_COperate.FuncConvert(m_deviceName,"DigSourceClose",m_com,m_channel,m_dllPath,m_funcName);//��ȡ����������dll������

	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //��ȡ�豸״̬
	string temp_s(status);
	if(temp_s=="Close")
		return 0;
	char hInitModule[20];
	//m_CShare.WriteToSharedMemory("У׼Դ���ӹر�");
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigSourceClose��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//����dll
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
			throw string("�Ҳ���У׼Դ�رպ���");
		}
		if(!FreeLibrary(hModule))
			throw string("ж�ض�̬���ӿ�ʧ��");

		//if(ret==0)
	//	{
			m_COperate.ReadHandles(m_com,"InitDllHandle",hInitModule);  //��ȡ��ʼ��dll���
			m_InitModule=(HMODULE)(atoi(hInitModule));
			FreeLibrary(m_InitModule);
			//if(!FreeLibrary(m_InitModule))
			//	throw string("ж�س�ʼ����̬���ӿ�ʧ��");
			m_COperate.WriteHandles(m_com,"DeviceStatus","Close"); //д���豸״̬
			m_CShare.WriteToSharedMemory("У׼Դ�����ѹر�");

	//	}
	//	else
	//	{
	//		m_CShare.WriteToSharedMemory("У׼Դ���ӹر�ʧ��");

	//	}

	}
	else
	{
		throw string("����У׼Դ�رճ����ʧ��");
	}

	return ret;
}

int CDigSource::DigSourceConfig(char* function, char* value, char* unit, char* freq,char* unit_Freq,char* currentPort)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigSourceConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//����dll
	MySet6 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet6)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,function,value,unit,freq,unit_Freq,currentPort);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���У׼Դ���ú���");
		}
	}
	else
	{
		throw string("����У׼Դ���ó����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}

int CDigSource::DigSourceOutSet(char* isOutSet)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceOutSet",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigSourceOutSet��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isOutSet);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���У׼Դ������ƺ���");
		}
	}
	else
	{
		throw string("����У׼Դ������Ƴ����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}
int CDigSource::DigSourceOffset(char* offsetValue)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceOffset",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigSourceOffset��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,offsetValue);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���У׼Դֱ��ƫ�����ú���");
		}
	}
	else
	{
		throw string("����У׼Դֱ��ƫ�����ó����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}
int CDigSource::DigSourceWaveSet(char* wave,char* duty)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceWaveSet",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigSourceWaveSet��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//����dll
	MySet1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,wave,duty);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���У׼Դֱ��ƫ�����ú���");
		}
	}
	else
	{
		throw string("����У׼Դֱ��ƫ�����ó����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}
int CDigSource::DigSourceReset(char* isReset)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"DigSourceReset",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���DigSourceReset��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(_T(m_dllPath));//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isReset);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���У׼Դ���ú���");
		}
	}
	else
	{
		throw string("����У׼Դ���ó����ʧ��");
	}
	//m_CShare.WriteToSharedMemory("�������");
	return ret;
}