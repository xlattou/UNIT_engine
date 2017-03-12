#include "stdafx.h"
#include "Spectrum.h"
using namespace std;

CSpectrum::CSpectrum(char* device,ShareMemory &myshare):m_CShare(myshare)
{
	strcpy(m_deviceName,device);
	strcpy(m_deviceHandle,"GPIB0::18::INSTR");
}

int CSpectrum::SpecInit(BOOL isReset)
{
	int ret=1;
	CString strTemp = "";
	m_COperate.FuncConvert(m_deviceName,"SpecInit",m_com,m_channel,m_dllPath,m_funcName);//��ȡ����������dll������
	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //��ȡ�豸״̬
	string temp_s(status);
	if(temp_s!="Open")
	{
		m_CShare.WriteToSharedMemory("Ƶ�׷����ǳ�ʼ��...");
		if(((string)m_funcName).empty())
		{
			throw string("�Ҳ���SpecInit��Ӧ��������Ϣ");
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
			throw string("����Ƶ�׷����ǳ�ʼ�������ʧ��");
		}
		if(ret==0)
		{
			m_CShare.WriteToSharedMemory("Ƶ�׷����ǳ�ʼ�����");
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
			m_CShare.WriteToSharedMemory("Ƶ�׷����ǳ�ʼ��ʧ��");
		}

	}
	else if(temp_s=="Open")
	{
		ret=2;
		m_COperate.ReadHandles(m_com,"DeviceOutHandle",m_deviceHandle);
		m_CShare.WriteToSharedMemory("Ƶ�׷�����������");
	}
	return ret;
}

int CSpectrum::SpecClose(int intSerial)
{
	int ret=1;
	if(intSerial!=-1)
		return 0;
	m_COperate.FuncConvert(m_deviceName,"SpecClose",m_com,m_channel,m_dllPath,m_funcName);//��ȡ����������dll������

	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //��ȡ�豸״̬
	string temp_s(status);
	if(temp_s=="Close")
		return 0;
	char hInitModule[20];
	m_CShare.WriteToSharedMemory("Ƶ�׷����ǹر�");
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecClose��Ӧ��������Ϣ");
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
			throw string("�Ҳ���Ƶ�׷����ǹرպ���");
		}
		if(!FreeLibrary(hModule))
			throw string("ж�ض�̬���ӿ�ʧ��");
		m_COperate.ReadHandles(m_com,"InitDllHandle",hInitModule);  //��ȡ��ʼ��dll���
		m_InitModule=(HMODULE)(atoi(hInitModule));

		FreeLibrary(m_InitModule);
		m_COperate.WriteHandles(m_com,"DeviceStatus","Close"); //д���豸״̬
		m_CShare.WriteToSharedMemory("Ƶ�׷����������ѹر�");
	}
	else
	{
		throw string("����Ƶ�׷����ǹرճ����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecRefLevelConfig(char* level)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecRefLevelConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecRefLevelConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,level);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷����ǲο���ƽ���ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷����ǲο���ƽ���ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecFreqConfig(char* freq)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecFreqConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecFreqConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,freq);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷���������Ƶ�����ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷���������Ƶ�����ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecSpanConfig(char* span)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecSpanConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecSpanConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,span);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����ɨƵ�������ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����ɨƵ�������ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecSweepConfig(char* isSingle,char* isAutoTime,char* SweepTime)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecSweepConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecSweepConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet5 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet5)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isSingle,isAutoTime,SweepTime);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����ɨ�����ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����ɨ�����ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecBandWidthConfig(char* RBW, char* VBW,char* AverageTimes)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecBandWidthConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecBandWidthConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet5 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet5)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,RBW,VBW,AverageTimes);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷����Ǵ������ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷����Ǵ�������ʧ��");
	}
	return ret;
}

int CSpectrum::SpecActiveMarker(char* markerNumber,char* activeMode,char* position)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecActiveMarker",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecActiveMarker��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet5 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet5)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,markerNumber,activeMode,position);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����Marker�����");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����Marker��������ʧ��");
	}
	return ret;
}

int CSpectrum::SpecMoveMarker(char* markerNumber,char* position)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecMoveMarker",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecMoveMarker��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,markerNumber,position);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����Marker���ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����Marker���ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecGetMarkerLevel(char* markNumber,char* level)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("Ƶ�׷����Ƕ�ȡMarker��ƽ");
	m_COperate.FuncConvert(m_deviceName,"SpecGetMarkerLevel",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecGetMarkerLevel��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,markNumber,level,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����Marker��ƽ��ȡ����");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����Marker��ƽ��ȡ�����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecGetMarkerFreq(char*markNumber,char* freq)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("Ƶ�׷����Ƕ�ȡMarkerƵ��");
	m_COperate.FuncConvert(m_deviceName,"SpecGetMarkerFreq",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecGetMarkerFreq��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,markNumber,freq,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����MarkerƵ�ʶ�ȡ����");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����MarkerƵ�ʶ�ȡ�����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecGetMarkerCount(char* markerNumber, char* freq)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("Ƶ�׷����Ƕ�ȡMarkerƵ��");
	m_COperate.FuncConvert(m_deviceName,"SpecGetMarkerCount",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecGetMarkerCount��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,markerNumber,freq,50);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����MarkerCountƵ�ʶ�ȡ����");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����MarkerCountƵ�ʶ�ȡ�����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecGetWave(char* waveData)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("Ƶ�׷����ǲ��ζ�ȡ");
	m_COperate.FuncConvert(m_deviceName,"SpecGetWave",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecGetWave��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MyPowerTest lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MyPowerTest)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,waveData,8000);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷����ǲ��ζ�ȡ����");
		}
	}
	else
	{
		throw string("����Ƶ�׷����ǲ��ζ�ȡ�����ʧ��");
	}
	return ret;
}


int CSpectrum::SpecAttenConfig(char* isAuto,char* attenuation)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecAttenConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecAttenConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isAuto,attenuation);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷���������˥�����ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷���������˥�����ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecDetectorConfig(char* mode)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecDetectorConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecDetectorConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,mode);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷����Ǽ첨ģʽ���ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷����Ǽ첨ģʽ���ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecTraceModeConfig(char* traceNumber,char* mode)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecTraceModeConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecTraceModeConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,traceNumber,mode);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����ɨ��ģʽ���ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����ɨ��ģʽ���ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecAllMarkerOff()
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecAllMarkerOff",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecAllMarkerOff��Ӧ��������Ϣ");
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
			throw string("�Ҳ���Ƶ�׷���������Marker�رպ���");
		}
	}
	else
	{
		throw string("����Ƶ�׷���������Marker�رճ����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecAllDeltaMarkerOff()
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecAllDeltaMarkerOff",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecAllDeltaMarkerOff��Ӧ��������Ϣ");
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
			throw string("�Ҳ���Ƶ�׷���������DeltaMarker�رպ���");
		}
	}
	else
	{
		throw string("����Ƶ�׷���������DeltaMarker�رճ����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecDeltaMarkerConfig(char* markerNumber,char* mode, char* position)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecDeltaMarkerConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecDeltaMarkerConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet5 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet5)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,markerNumber,mode,position);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����DeltaMarker���ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����DeltaMarker���ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecSetLimitLine(char* mode,char* lineNumber,char* isDisplay, char* position)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecSetLimitLine",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecSetLimitLine��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,mode,lineNumber,isDisplay,position);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷����ǽ������ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷����ǽ������ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecReadFileFromIns(char* source,char* dest)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecReadFileFromIns",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecReadFileFromIns��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet1 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet1)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,source,dest);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷������ļ���ȡ����");
		}
	}
	else
	{
		throw string("����Ƶ�׷������ļ���ȡ�����ʧ��");
	}
	return ret;
}
int CSpectrum::SpecHardcopyToFile(char*deviceNumber,char* fileName,char* dataFormat,char* pageOrientation)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecHardcopyToFile",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecHardcopyToFile��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,deviceNumber,fileName,dataFormat,pageOrientation);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷����ǽ�������");
		}
	}
	else
	{
		throw string("����Ƶ�׷����ǽ��������ʧ��");
	}
	return ret;
}

int CSpectrum::SpecAmpConfig(char*isLog,char* LogScale,char* unit)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecAmpConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecAmpConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet5 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet5)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isLog,LogScale,unit);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷����ǵ�ƽ���ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷����ǵ�ƽ���ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecMarkerCount(char* markerNumber, char* isCount, char* gateTime)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecMarkerCount",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecMarkerCount��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet5 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet5)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,markerNumber,isCount,gateTime);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����Count���ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����Count�����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecInputCoupleSet(char* isDC)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecInputCoupleSet",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecInputCoupleSet��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isDC);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����������ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����������ó����ʧ��");
	}
	return ret;
}

int CSpectrum::ReceiverPreAmpConfig(char* isOn)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"ReceiverPreAmpConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���ReceiverPreAmpConfig��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,isOn);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����Ԥ�������ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����Ԥ�������ó����ʧ��");
	}
	return ret;
}

int CSpectrum::SpecRBWTest(char* waveData,int NdB,char* RBW)
{
	int ret=1;
	CString strInputString=waveData;
	CString strTemp=strInputString;
	if(strTemp.IsEmpty())
		return 0;
	int pos1=strTemp.Find(",");
	float fFreqStart=atof(strTemp.Left(pos1));  //Ƶ����ʼֵ

	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	float fIncrease=atof(strTemp.Left(pos1)); //����
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	int fLength=atoi(strTemp.Left(pos1)); //���γ���
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	float fRefLevel=atof(strTemp.Left(pos1)); //�ο���ƽ
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	if(fLength==0)
		return 0;
	////////////////////////�Ӳ��������ж�ȡ��ƽ�����Ƶ������//////////////////////////////////////////////////
	float *levelArr=new float[fLength];
	float *freqArr =new float[fLength];

	for(int i=0;i<fLength-1;i++)
	{
		if(!strTemp.IsEmpty())
		{
			pos1=strTemp.Find(",");
			levelArr[i]=atof(strTemp.Left(pos1));
        	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
			freqArr[i]=fFreqStart+fIncrease*i;
		}
	}
	levelArr[fLength-1]=atof(strTemp);
	freqArr[fLength-1]=fFreqStart+fIncrease*fLength;
	//////////////////////��ȡ��ֵ����///////////////////////////////////////////////////////////////////////////////////////
    float peakLevel=levelArr[0];
	int intIndex=0;
	for(int i=1;i<fLength-1;i++)
	{
		if(levelArr[i]>peakLevel)
		{
			peakLevel=levelArr[i];
			intIndex=i;
		}
	}
	/////////////////////��ȡ����NdB��ƽ���Ƶ��////////////////////////////////////////////////////////////////////////////
    float fLevel_NdB=peakLevel-NdB;
	float fMinLeft=levelArr[0];
	int intIndexLeft=0;
	for(int i=1;i<intIndex;i++)
	{
		if(abs(levelArr[i]-fLevel_NdB)<abs(fMinLeft-fLevel_NdB))
		{
			fMinLeft=levelArr[i];
			intIndexLeft=i;

		}
	}
	float fMinRight=levelArr[intIndex+1];
	int intIndexRight=intIndex+1;
	for(int i=intIndex+2;i<fLength-1;i++)
	{
		if(abs(levelArr[i]-fLevel_NdB)<abs(fMinRight-fLevel_NdB))
		{
			fMinRight=levelArr[i];
			intIndexRight=i;
		}
	}
	CString strResult="";
	strResult.Format("%.2f",(intIndexRight-intIndexLeft)*fIncrease);
	_tcscpy(RBW,strResult.GetBuffer());
	delete [] levelArr;
	delete [] freqArr;
	return ret;
}

int CSpectrum::SpecRBWTestM(char* waveData,int NdB,char* RBW,char* marker1,char*marker2)
{
	int ret=1;
	CString strInputString=waveData;
	CString strTemp=strInputString;
	if(strTemp.IsEmpty())
		return 0;
	int pos1=strTemp.Find(",");
	float fFreqStart=atof(strTemp.Left(pos1));  //Ƶ����ʼֵ

	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	float fIncrease=atof(strTemp.Left(pos1)); //����
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	int fLength=atoi(strTemp.Left(pos1)); //���γ���
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	float fRefLevel=atof(strTemp.Left(pos1)); //�ο���ƽ
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	if(fLength==0)
		return 0;
	////////////////////////�Ӳ��������ж�ȡ��ƽ�����Ƶ������//////////////////////////////////////////////////
	float *levelArr=new float[fLength];
	float *freqArr =new float[fLength];

	for(int i=0;i<fLength-1;i++)
	{
		if(!strTemp.IsEmpty())
		{
			pos1=strTemp.Find(",");
			levelArr[i]=atof(strTemp.Left(pos1));
			strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
			freqArr[i]=fFreqStart+fIncrease*i;
		}
	}
	levelArr[fLength-1]=atof(strTemp);
	freqArr[fLength-1]=fFreqStart+fIncrease*fLength;
	//////////////////////��ȡ��ֵ����///////////////////////////////////////////////////////////////////////////////////////
	float peakLevel=levelArr[0];
	int intIndex=0;
	for(int i=1;i<fLength-1;i++)
	{
		if(levelArr[i]>peakLevel)
		{
			peakLevel=levelArr[i];
			intIndex=i;
		}
	}
	/////////////////////��ȡ����NdB��ƽ���Ƶ��////////////////////////////////////////////////////////////////////////////
	float fLevel_NdB=peakLevel-NdB;
	float fMinLeft=levelArr[0];
	int intIndexLeft=0;
	for(int i=1;i<intIndex;i++)
	{
		if(abs(levelArr[i]-fLevel_NdB)<abs(fMinLeft-fLevel_NdB))
		{
			fMinLeft=levelArr[i];
			intIndexLeft=i;

		}
	}
	float fMinRight=levelArr[intIndex+1];
	int intIndexRight=intIndex+1;
	for(int i=intIndex+2;i<fLength-1;i++)
	{
		if(abs(levelArr[i]-fLevel_NdB)<abs(fMinRight-fLevel_NdB))
		{
			fMinRight=levelArr[i];
			intIndexRight=i;
		}
	}
	CString strResult="";
	CString strMarker1="";
	CString strMarker2="";
	strResult.Format("%.2f",(intIndexRight-intIndexLeft)*fIncrease);
	strMarker1.Format("%.9f",freqArr[intIndexLeft]);
	strMarker2.Format("%.9f",freqArr[intIndexRight]);
	_tcscpy(RBW,strResult.GetBuffer());
	_tcscpy(marker1,strMarker1.GetBuffer());
	_tcscpy(marker2,strMarker2.GetBuffer());
	delete [] levelArr;
	delete [] freqArr;
	return ret;
}

int	CSpectrum::SpecContinuous(char* continMode)
{
	int ret=1;
	
	m_COperate.FuncConvert(m_deviceName,"SpecContinuous",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("�Ҳ���SpecContinuous��Ӧ��������Ϣ");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//����dll
	MySet4 lpFunc=NULL;
	if(hModule)
	{
		lpFunc=(MySet4)GetProcAddress(hModule,m_funcName);
		if(lpFunc)
		{
			ret=lpFunc(m_deviceHandle,continMode);
		}
		else
		{
			if(!FreeLibrary(hModule))
				throw string("ж�ض�̬���ӿ�ʧ��");
			throw string("�Ҳ���Ƶ�׷�����Ԥ�������ú���");
		}
	}
	else
	{
		throw string("����Ƶ�׷�����Ԥ�������ó����ʧ��");
	}
	return ret;
}


CSpectrum::~CSpectrum(void)
{
}
