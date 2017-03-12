#include "stdafx.h"
#include "SignalGen.h"

CSignalGen::CSignalGen(char* device,ShareMemory &myshare):m_CShare(myshare)
{
	strcpy(m_deviceName,device);
}

CSignalGen::~CSignalGen(void)
{

}

void CSignalGen::RegGetSN(char VISA[], char SN[], int16_t *ret, int32_t len)
{
	m_COperate.FuncConvert(m_deviceName,"GetSN",m_dllPath,m_funcName);//��TestConfig�ļ��е�ini�ļ��ж�ȡ�豸�߼�����,�����߼�����,dll�ļ���ַ,��������
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���GetSN��Ӧ��������Ϣ");
	}

	int ret1=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet15 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet15)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret1=lpFunc(VISA,SN,ret,len);
		}
		else
		{
			throw string("�Ҳ�����̬�⺯��");
		}
		FreeLibrary(hModule);
	}
}

int16_t CSignalGen::RegRFDigModeOutSet(char VISA[], char ModeStateOut[])
{
	m_COperate.FuncConvert(m_deviceName,"RFDigModeOutSet",m_dllPath,m_funcName);//��TestConfig�ļ��е�ini�ļ��ж�ȡ�豸�߼�����,�����߼�����,dll�ļ���ַ,��������
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���RFDigModeOutSet��Ӧ��������Ϣ");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeStateOut);
		}
		else
		{
			throw string("�Ҳ�����̬�⺯��");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int16_t CSignalGen::RegRFGenClose(char VISA[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenClose",m_dllPath,m_funcName);//��TestConfig�ļ��е�ini�ļ��ж�ȡ�豸�߼�����,�����߼�����,dll�ļ���ַ,��������
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���RFGenClose��Ӧ��������Ϣ");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet10 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet10)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA);
		}
		else
		{
			throw string("�Ҳ�����̬�⺯��");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int16_t CSignalGen::RegRFGenDigModeSet(char VISA[], char ModeStateArb[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenDigModeSet",m_dllPath,m_funcName);//��TestConfig�ļ��е�ini�ļ��ж�ȡ�豸�߼�����,�����߼�����,dll�ļ���ַ,��������
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���RFGenDigModeSet��Ӧ��������Ϣ");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeStateArb);
		}
		else
		{
			throw string("�Ҳ�����̬�⺯��");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

void CSignalGen::RegRFGenInit(char VISA[], char ModeReset[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenInit",m_dllPath,m_funcName);//��TestConfig�ļ��е�ini�ļ��ж�ȡ�豸�߼�����,�����߼�����,dll�ļ���ַ,��������
	
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���RFGenInit��Ӧ��������Ϣ");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeReset);
		}
		else
		{
			throw string("RFGeninit�Ҳ�����̬�⺯��");
		}
		FreeLibrary(hModule);
	}
}

int16_t CSignalGen::RegRFGenOutSet(char VISA[], char ModeOutput[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenOutSet",m_dllPath,m_funcName);//��TestConfig�ļ��е�ini�ļ��ж�ȡ�豸�߼�����,�����߼�����,dll�ļ���ַ,��������
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���RFGenOutSet��Ӧ��������Ϣ");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,ModeOutput);
		}
		else
		{
			throw string("�Ҳ�����̬�⺯��");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int16_t CSignalGen::RegRFGenSelectDigWave(char VISA[], char WaveName[])
{
	CString strTemp = "";
	strTemp.Format("%s",WaveName);
	AfxMessageBox(strTemp);

	m_COperate.FuncConvert(m_deviceName,"RFGenSelectDigWave",m_dllPath,m_funcName);//��TestConfig�ļ��е�ini�ļ��ж�ȡ�豸�߼�����,�����߼�����,dll�ļ���ַ,��������
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���RFGenSelectDigWave��Ӧ��������Ϣ");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,WaveName);
		}
		else
		{
			throw string("111�Ҳ�����̬�⺯��");
		}
		FreeLibrary(hModule);
	}
	return 0;
}

int16_t CSignalGen::RegRFGenSet(char VISA[], char FreqHz[], char AmpDBm[])
{
	m_COperate.FuncConvert(m_deviceName,"RFGenSet",m_dllPath,m_funcName);//��TestConfig�ļ��е�ini�ļ��ж�ȡ�豸�߼�����,�����߼�����,dll�ļ���ַ,��������

	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���RFGenSet��Ӧ��������Ϣ");
	}

	int ret=1;
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(VISA,FreqHz,AmpDBm);
		}
		else
		{
			throw string("5555�Ҳ�����̬�⺯��");
		}
		FreeLibrary(hModule);
	}
	return 0;
}