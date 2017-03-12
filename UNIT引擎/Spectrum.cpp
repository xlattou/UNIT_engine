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
	m_COperate.FuncConvert(m_deviceName,"SpecInit",m_com,m_channel,m_dllPath,m_funcName);//获取函数所属的dll和名称
	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //读取设备状态
	string temp_s(status);
	if(temp_s!="Open")
	{
		m_CShare.WriteToSharedMemory("频谱分析仪初始化...");
		if(((string)m_funcName).empty())
		{
			throw string("找不到SpecInit对应的驱动信息");
		}
		m_InitModule=LoadLibrary(m_dllPath);//调用dll
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
					throw string("卸载动态链接库失败");
				throw string("找不到初始化函数");
			}
		}
		else
		{
			throw string("加载频谱分析仪初始化程序库失败");
		}
		if(ret==0)
		{
			m_CShare.WriteToSharedMemory("频谱分析仪初始化完成");
			int isWrite1=m_COperate.WriteHandles(m_com,"DeviceOutHandle",m_deviceHandle);  //写入设备地址
			int isWrite2=m_COperate.WriteHandles(m_com,"DeviceStatus","Open"); //写入设备状态
			char hModule[20];
			sprintf_s(hModule,20,"%d",(int)(m_InitModule));
			m_COperate.WriteHandles(m_com,"InitDllHandle",hModule); //写入初始化dll句柄
			if((isWrite2|isWrite2)==0)
			{
				throw string("状态写入失败");
			}
		}
		else
		{
			m_CShare.WriteToSharedMemory("频谱分析仪初始化失败");
		}

	}
	else if(temp_s=="Open")
	{
		ret=2;
		m_COperate.ReadHandles(m_com,"DeviceOutHandle",m_deviceHandle);
		m_CShare.WriteToSharedMemory("频谱分析仪已启动");
	}
	return ret;
}

int CSpectrum::SpecClose(int intSerial)
{
	int ret=1;
	if(intSerial!=-1)
		return 0;
	m_COperate.FuncConvert(m_deviceName,"SpecClose",m_com,m_channel,m_dllPath,m_funcName);//获取函数所属的dll和名称

	char status[10];
	m_COperate.ReadHandles(m_com,"DeviceStatus",status);  //读取设备状态
	string temp_s(status);
	if(temp_s=="Close")
		return 0;
	char hInitModule[20];
	m_CShare.WriteToSharedMemory("频谱分析仪关闭");
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecClose对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
			throw string("找不到频谱分析仪关闭函数");
		}
		if(!FreeLibrary(hModule))
			throw string("卸载动态链接库失败");
		m_COperate.ReadHandles(m_com,"InitDllHandle",hInitModule);  //读取初始化dll句柄
		m_InitModule=(HMODULE)(atoi(hInitModule));

		FreeLibrary(m_InitModule);
		m_COperate.WriteHandles(m_com,"DeviceStatus","Close"); //写入设备状态
		m_CShare.WriteToSharedMemory("频谱分析仪连接已关闭");
	}
	else
	{
		throw string("加载频谱分析仪关闭程序库失败");
	}
	return ret;
}

int CSpectrum::SpecRefLevelConfig(char* level)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecRefLevelConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecRefLevelConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪参考电平设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪参考电平设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecFreqConfig(char* freq)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecFreqConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecFreqConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪中心频率设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪中心频率设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecSpanConfig(char* span)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecSpanConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecSpanConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪扫频带宽设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪扫频带宽设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecSweepConfig(char* isSingle,char* isAutoTime,char* SweepTime)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecSweepConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecSweepConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪扫描设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪扫描设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecBandWidthConfig(char* RBW, char* VBW,char* AverageTimes)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecBandWidthConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecBandWidthConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪带宽设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪带宽程序库失败");
	}
	return ret;
}

int CSpectrum::SpecActiveMarker(char* markerNumber,char* activeMode,char* position)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecActiveMarker",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecActiveMarker对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪Marker激活函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪Marker激活程序库失败");
	}
	return ret;
}

int CSpectrum::SpecMoveMarker(char* markerNumber,char* position)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecMoveMarker",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecMoveMarker对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪Marker设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪Marker设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecGetMarkerLevel(char* markNumber,char* level)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("频谱分析仪读取Marker电平");
	m_COperate.FuncConvert(m_deviceName,"SpecGetMarkerLevel",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecGetMarkerLevel对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪Marker电平读取函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪Marker电平读取程序库失败");
	}
	return ret;
}

int CSpectrum::SpecGetMarkerFreq(char*markNumber,char* freq)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("频谱分析仪读取Marker频率");
	m_COperate.FuncConvert(m_deviceName,"SpecGetMarkerFreq",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecGetMarkerFreq对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪Marker频率读取函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪Marker频率读取程序库失败");
	}
	return ret;
}

int CSpectrum::SpecGetMarkerCount(char* markerNumber, char* freq)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("频谱分析仪读取Marker频率");
	m_COperate.FuncConvert(m_deviceName,"SpecGetMarkerCount",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecGetMarkerCount对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪MarkerCount频率读取函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪MarkerCount频率读取程序库失败");
	}
	return ret;
}

int CSpectrum::SpecGetWave(char* waveData)
{
	int ret=1;
	//m_CShare.WriteToSharedMemory("频谱分析仪波形读取");
	m_COperate.FuncConvert(m_deviceName,"SpecGetWave",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecGetWave对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪波形读取函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪波形读取程序库失败");
	}
	return ret;
}


int CSpectrum::SpecAttenConfig(char* isAuto,char* attenuation)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecAttenConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecAttenConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪输入衰减设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪输入衰减设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecDetectorConfig(char* mode)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecDetectorConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecDetectorConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪检波模式设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪检波模式设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecTraceModeConfig(char* traceNumber,char* mode)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecTraceModeConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecTraceModeConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪扫描模式设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪扫描模式设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecAllMarkerOff()
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecAllMarkerOff",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecAllMarkerOff对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪所有Marker关闭函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪所有Marker关闭程序库失败");
	}
	return ret;
}

int CSpectrum::SpecAllDeltaMarkerOff()
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecAllDeltaMarkerOff",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecAllDeltaMarkerOff对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪所有DeltaMarker关闭函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪所有DeltaMarker关闭程序库失败");
	}
	return ret;
}

int CSpectrum::SpecDeltaMarkerConfig(char* markerNumber,char* mode, char* position)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecDeltaMarkerConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecDeltaMarkerConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪DeltaMarker设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪DeltaMarker设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecSetLimitLine(char* mode,char* lineNumber,char* isDisplay, char* position)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecSetLimitLine",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecSetLimitLine对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪界限设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪界限设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecReadFileFromIns(char* source,char* dest)
{
	int ret=1;
	m_COperate.FuncConvert(m_deviceName,"SpecReadFileFromIns",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecReadFileFromIns对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪文件读取函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪文件读取程序库失败");
	}
	return ret;
}
int CSpectrum::SpecHardcopyToFile(char*deviceNumber,char* fileName,char* dataFormat,char* pageOrientation)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecHardcopyToFile",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecHardcopyToFile对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪截屏函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪截屏程序库失败");
	}
	return ret;
}

int CSpectrum::SpecAmpConfig(char*isLog,char* LogScale,char* unit)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecAmpConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecAmpConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪电平设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪电平设置程序库失败");
	}
	return ret;
}

int CSpectrum::SpecMarkerCount(char* markerNumber, char* isCount, char* gateTime)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecMarkerCount",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecMarkerCount对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪Count设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪Count程序库失败");
	}
	return ret;
}

int CSpectrum::SpecInputCoupleSet(char* isDC)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"SpecInputCoupleSet",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到SpecInputCoupleSet对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪耦合设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪耦合设置程序库失败");
	}
	return ret;
}

int CSpectrum::ReceiverPreAmpConfig(char* isOn)
{
	int ret=1;

	m_COperate.FuncConvert(m_deviceName,"ReceiverPreAmpConfig",m_dllPath,m_funcName);
	if(((string)m_funcName).empty())
	{
		throw string("找不到ReceiverPreAmpConfig对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪预加重设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪预加重设置程序库失败");
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
	float fFreqStart=atof(strTemp.Left(pos1));  //频率起始值

	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	float fIncrease=atof(strTemp.Left(pos1)); //增量
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	int fLength=atoi(strTemp.Left(pos1)); //波形长度
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	float fRefLevel=atof(strTemp.Left(pos1)); //参考电平
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	if(fLength==0)
		return 0;
	////////////////////////从波形数据中读取电平数组和频率数组//////////////////////////////////////////////////
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
	//////////////////////读取峰值数据///////////////////////////////////////////////////////////////////////////////////////
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
	/////////////////////读取左右NdB电平点的频率////////////////////////////////////////////////////////////////////////////
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
	float fFreqStart=atof(strTemp.Left(pos1));  //频率起始值

	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	float fIncrease=atof(strTemp.Left(pos1)); //增量
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	int fLength=atoi(strTemp.Left(pos1)); //波形长度
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	pos1=strTemp.Find(",");
	float fRefLevel=atof(strTemp.Left(pos1)); //参考电平
	strTemp=strTemp.Right(strTemp.GetLength()-(pos1+1));
	if(fLength==0)
		return 0;
	////////////////////////从波形数据中读取电平数组和频率数组//////////////////////////////////////////////////
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
	//////////////////////读取峰值数据///////////////////////////////////////////////////////////////////////////////////////
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
	/////////////////////读取左右NdB电平点的频率////////////////////////////////////////////////////////////////////////////
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
		throw string("找不到SpecContinuous对应的驱动信息");
	}
	HMODULE hModule=LoadLibrary(m_dllPath);//调用dll
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
				throw string("卸载动态链接库失败");
			throw string("找不到频谱分析仪预加重设置函数");
		}
	}
	else
	{
		throw string("加载频谱分析仪预加重设置程序库失败");
	}
	return ret;
}


CSpectrum::~CSpectrum(void)
{
}
