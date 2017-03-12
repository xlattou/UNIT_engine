#include "stdafx.h"
#include "OperateFunc.h"


CString COperateFunc::m_strTestConfig="";


COperateFunc::COperateFunc(void)
{
}

/************************************************************************/
/* 进行设备功能定位，通过逻辑名称定位到dll和函数名                                                                     */
/************************************************************************/
/////////////////////////////////////////////////////

int COperateFunc::FuncConvert(char* deviceName,//设备逻辑名称
							 char* logicalName,//功能逻辑名称
							 char* com,  //设备的物理地址
							 char* channel,//设备通道
							 char* dllPath,//dll文件地址
							 char* funcName //函数名称
							 )
{
	
	char s[255];
	char temp[255];
	char fPath[255];
	char szDllFolder[MAX_PATH];
	GetModuleFileName(NULL,szDllFolder,MAX_PATH);//                D:\山锋测控\ATE_TEST\ATE_TEST.EXE
	(_tcsrchr(szDllFolder,_T('\\')))[0] = 0;  //去掉ATE_TEST.exe   D:\山锋测控\ATE_TEST
	(_tcsrchr(szDllFolder,_T('\\')))[1] = 0;//去掉\\Debug          D:\山锋测控
	_tcscpy(s,szDllFolder);
	string s_temp(s);

	//s_temp+="\\data.ini";
	//strToChar(s_temp,s);
	int mark=GetPrivateProfileString(deviceName,logicalName,"Error",temp,255,m_strTestConfig);       //从Ini文件中取逻辑功能映射字符串
	if(mark==0)
	{
		throw string("读取配置文件失败");
		return 0;
	}
	string s1(temp); 
	
	int pos1=s1.find("->");        //  从功能字符串中查找仪器的逻辑名称
    string dllName="";
	string myfuncName="";
	if(string::npos!=pos1)
	{
		dllName=s1.substr(0,pos1);
		myfuncName=s1.substr(pos1+2);
	}
    GetPrivateProfileString(deviceName,"Address","Error",com,255,m_strTestConfig);
	GetPrivateProfileString(deviceName,"Channel","Error",channel,255,m_strTestConfig);
	GetPrivateProfileString(deviceName,"DriverName","Error",fPath,255,m_strTestConfig);
	//string mydllPath=(string)fPath+"\\"+dllName; 
	string mydllPath=s_temp+"DataInfo\\UUTTestInfo\\"+(string)fPath+"\\"+dllName;
	
	strToChar(mydllPath,dllPath);
	strToChar(myfuncName,funcName);
	return 1;
}
//功能映射
int COperateFunc::FuncConvert(char* deviceName,//设备逻辑名称
							  char* logicalName,//功能逻辑名称
							  char* dllPath,//dll文件地址
							  char* funcName //函数名称
							  )
{
	char s[255];
	char temp[255];
	char fPath[255];
	char szDllFolder[MAX_PATH];
	GetModuleFileName(NULL,szDllFolder,MAX_PATH);
	(_tcsrchr(szDllFolder,_T('\\')))[0] = 0;  //去掉ATE_TEST.exe
	(_tcsrchr(szDllFolder,_T('\\')))[1] = 0;//去掉\\Debug
	_tcscpy(s,szDllFolder);
	string s_temp(s);
	//s_temp+="\\data.ini";
	//strToChar(s_temp,s);
	int mark=GetPrivateProfileString(deviceName,logicalName,"Error",temp,255,m_strTestConfig);       //从Ini文件中取逻辑功能映射字符串
	if(mark==0)
	{
		throw string("读取配置文件失败");
		return 0;
	}
	string s1(temp);                        
	int pos1=s1.find("->");        //  从功能字符串中查找仪器的逻辑名称
    string dllName="";
	string myfuncName="";
	if(string::npos!=pos1)
	{
		dllName=s1.substr(0,pos1);
		myfuncName=s1.substr(pos1+2);
	}
	GetPrivateProfileString(deviceName,"DriverName","Error",fPath,255,m_strTestConfig);
	//string mydllPath=(string)fPath+"\\"+dllName;  
	string mydllPath=s_temp+"DataInfo\\UUTTestInfo\\"+(string)fPath+"\\"+dllName;
	strToChar(mydllPath,dllPath);
	strToChar(myfuncName,funcName);
	return 1;
}


/*******************************************从指定的映射字符串中按照逻辑名称读取对应的数据******************************************/
int COperateFunc::GetFunc(char *inputString, char *LogicName,char* myString)
{
	string s=inputString;	
	bool isMatch=true;
	string result="";
    string temp_Logic=LogicName;
	string temp="";
	while(isMatch&&(int)s.length()>0)
	{
		string::size_type pos1=s.find(";");
		if(pos1!=string::npos)
		{
	    	temp=s.substr(0,pos1);
	    	s=s.substr(pos1+1);
		}
		else
		{
			temp=s;
			s="";
		}
		string::size_type pos2=temp.find("=");
		if(pos2!=string::npos&&temp.substr(0,pos2)==LogicName)
		{
			result=temp.substr(pos2+1);
			break;
		}
	}
	if(!result.empty())
	{
		for(int i=0;i<(int)result.length()+1;i++)
		{
			myString[i]=result[i];
		}
	}
	return 1;
}
/*******************************************字符串分割******************************************/
int COperateFunc::StringSplit(char *inputString, char *regular, char *X, char *Y)
{
	char* temp=new char[50];
	
	GetFunc(inputString,regular,temp);//从指定的映射字符串中按照逻辑名称读取对应的数据
	string s=temp;

	
	string::size_type pos1=s.find("_");
    string s_X="";
	string s_Y="";

	if(string::npos==pos1)
	{
		s_X=s;
	}
	else
	{
	   s_X=s.substr(0,pos1);
	   s_Y=s.substr(pos1+1);
	}

	strToChar(s_X,X);
	strToChar(s_Y,Y);
	delete[] temp;
	return 1;	
}
void COperateFunc::strToChar(std::string s, char *result)
{
	for(int i=0;i<(int)s.length()+1;i++)
	{
		result[i]=s[i];
	}
}
double COperateFunc::stringToDouble(std::string s)
{
	char temp[50]={'\0'};
	for(int i=0;i<(int)s.length()+1;i++)
	{
		temp[i]=s[i];
	}
	return atof(temp);
}
int COperateFunc::stringToInt(std::string s)
{
	char temp[50]={'\0'};
	for(int i=0;i<(int)s.length()+1;i++)
	{
		temp[i]=s[i];
	}
	return atoi(temp);
}



/*******************************************从ATS.ini读取运行状态*******************************************/
int COperateFunc::GetRunStatus()
{
	char* s=new char[255];
	char szDllFolder[MAX_PATH];
	GetModuleFileName(NULL,szDllFolder,MAX_PATH); //获得程序路径
	(_tcsrchr(szDllFolder,_T('\\')))[1]=0; //获取程序运行目录
	_tcscpy(s,szDllFolder);
	string s_temp(s);
	s_temp+="\\DeviceHandle.ini";
	strToChar(s_temp,s);
	char temp[10];
	int mark=GetPrivateProfileString("RunStatus","TP","Error",temp,10,s);       //从Ini文件中取逻辑功能映射字符串
	if(mark==0)
	{
		delete[] s;
		return 0;
	}
	else
	{
		delete[] s;
		return atoi(temp);
	}

}


/*******************************************往DeviceHandle.ini写入源名柄*******************************************/
int COperateFunc::WriteHandles(char *deviceName, char *handle)
{
	char* s=new char[255];
	char szDllFolder[MAX_PATH];
	GetModuleFileName(NULL,szDllFolder,MAX_PATH); //获得程序路径
	(_tcsrchr(szDllFolder,_T('\\')))[1]=0; //获取程序运行目录
	_tcscpy(s,szDllFolder);
	string s_temp(s); //转换为string格式
	s_temp+="\\DeviceHandle.ini";
	strToChar(s_temp,s);
	BOOL isWrite=WritePrivateProfileString(deviceName,"DeviceStatus",handle,s);
	delete[] s;
    return isWrite;
}
/*******************************************从DeviceHandle.ini读取源名柄*******************************************/
int COperateFunc::ReadHandles(char *deviceName,char* handle)
{
	char* s=new char[255];
	char szDllFolder[MAX_PATH];
	GetModuleFileName(NULL,szDllFolder,MAX_PATH); //获得程序路径
	(_tcsrchr(szDllFolder,_T('\\')))[1]=0; //获取程序运行目录
	_tcscpy(s,szDllFolder);
	string s_temp(s);
	s_temp+="\\DeviceHandle.ini";
	strToChar(s_temp,s);
	int mark=GetPrivateProfileString(deviceName,"Handle","Error",handle,50,s);       //从Ini文件中取逻辑功能映射字符串
	delete[] s;
	return mark;
}

/*******************************************往DeviceHandle.ini写入源名柄*******************************************/
int COperateFunc::WriteHandles(char *deviceName,char* key,char *handle)
{
	char* s=new char[255];
	char szDllFolder[MAX_PATH];
	GetModuleFileName(NULL,szDllFolder,MAX_PATH); //获得程序路径
	(_tcsrchr(szDllFolder,_T('\\')))[1]=0; //获取程序运行目录
	_tcscpy(s,szDllFolder);
	string s_temp(s); //转换为string格式
	s_temp+="\\DeviceHandle.ini";
	strToChar(s_temp,s);
	BOOL isWrite=WritePrivateProfileString(deviceName,key,handle,s);
	delete[] s;
    return isWrite;
}

/*******************************************从DeviceHandle.ini读取源名柄*******************************************/
int COperateFunc::ReadHandles(char *deviceName,char* key,char* handle)
{
	char* s=new char[255];
	char szDllFolder[MAX_PATH];
	GetModuleFileName(NULL,szDllFolder,MAX_PATH); //获得程序路径
	(_tcsrchr(szDllFolder,_T('\\')))[1]=0; //获取程序运行目录
	_tcscpy(s,szDllFolder);
	string s_temp(s);
	s_temp+="\\DeviceHandle.ini";
	strToChar(s_temp,s);
	int mark=GetPrivateProfileString(deviceName,key,"Error",handle,50,s);       //从Ini文件中取逻辑功能映射字符串
	delete[] s;
	return mark;
}

//int COperateFunc::ShowMessage(char* message)
//{
//	CFrm_Message frm_Message((CString)message);
//	frm_Message.DoModal();
//	return 1;
//}

int COperateFunc::ShowMessage(char* message,char* flag)
{

	if(strcmp(flag,"OPEN")==0)
	{

			/*Frm_Message frm_Message((CString)message);
			frm_Message.DoModal();*/
		m_Pfrm_Message = new Frm_Message((CString)message);
			m_Pfrm_Message->Create(IDD_DIALOG_MESSAGE);
			m_Pfrm_Message->ShowWindow(SW_SHOW);

			//Sleep(1000);
		///*m_Pfrm_Message = new Frm_Message(NULL);
		//m_Pfrm_Message->Create(IDD_DIALOG_MESSAGE,NULL);
		//m_Pfrm_Message->ShowWindow(SW_SHOW);*/





	}
	else
	{
			m_Pfrm_Message->DestroyWindow();
			delete m_Pfrm_Message;
	}

	return 1;
}

int COperateFunc::WriteStatusCache(char* cacheName,char* value)
{
	char* s=new char[MAX_PATH];
	GetModuleFileName(NULL,s,MAX_PATH); //获得程序路径
	(_tcsrchr(s,_T('\\')))[1]=0; //获取程序运行目录
	CString s_temp(s);
	s_temp+="DeviceHandle.ini";
	CString myValue="";
	myValue.Format("status=1;value=%s",value);
	int mark=WritePrivateProfileString("TPStatusCache",cacheName,myValue,s_temp);
	delete [] s;
	return mark;
}
//////////////////////////////////////////////////////////////////////////

int COperateFunc::ReadStatusCache(char* cacheName,char* value,char* status)
{
	char szTemp[255];
	CString strValue="";
	CString strStatus="";
	char s[MAX_PATH];
	GetModuleFileName(NULL,s,MAX_PATH); //获得程序路径
	(_tcsrchr(s,_T('\\')))[1]=0; //获取程序运行目录
	CString s_temp(s);
	s_temp+="DeviceHandle.ini";
	int mark=GetPrivateProfileString("TPStatusCache",cacheName,"Error",szTemp,50,s_temp);       //从Ini文件中取逻辑功能映射字符串
	if(mark==0)
	{
		strStatus="0";
		strValue="";
		return 0;
	}
	s_temp=szTemp;
	int intStart=s_temp.Find(";");
	if(intStart==-1)
	{
		strStatus="0";
		strValue="";
		return 0;
	}
	CString strLeft=s_temp.Left(intStart);
	CString strRight=s_temp.Right(s_temp.GetLength()-(intStart+1));
	int intPos1=strLeft.Find("=");
	strStatus=strLeft.Right(strLeft.GetLength()-(intPos1+1));
	int intPos2=strRight.Find("=");
	strValue=strRight.Right(strRight.GetLength()-(intPos2+1));
	_tcscpy(value,strValue.GetBuffer());
	_tcscpy(status,strStatus.GetBuffer());
	return mark;
}
int COperateFunc::WriteStatusCache_M(char* cacheName,char* value1,char* value2)
{
	char* s=new char[MAX_PATH];
	GetModuleFileName(NULL,s,MAX_PATH); //获得程序路径
	(_tcsrchr(s,_T('\\')))[1]=0; //获取程序运行目录
	CString s_temp(s);
	s_temp+="DeviceHandle.ini";
	CString myValue="";
	myValue.Format("value1=%s;value2=%s",value1,value2);
	int mark=WritePrivateProfileString("TPStatusCache",cacheName,myValue,s_temp);
	delete [] s;
	return mark;
}

int COperateFunc::ReadStatusCache_M(char* cacheName, char* value1, char* value2)
{
	char szTemp[255];
	CString strValue1="";
	CString strValue2="";
	char s[MAX_PATH];
	GetModuleFileName(NULL,s,MAX_PATH); //获得程序路径
	(_tcsrchr(s,_T('\\')))[1]=0; //获取程序运行目录
	CString s_temp(s);
	s_temp+="DeviceHandle.ini";
	int mark=GetPrivateProfileString("TPStatusCache",cacheName,"Error",szTemp,50,s_temp);       //从Ini文件中取逻辑功能映射字符串
	if(mark==0)
	{
		strValue1="";
		strValue2="";
		return 0;
	}
	s_temp=szTemp;
	int intStart=s_temp.Find(";");
	if(intStart==-1)
	{
		strValue1="";
		strValue2="";
		return 0;
	}
	CString strLeft=s_temp.Left(intStart);
	CString strRight=s_temp.Right(s_temp.GetLength()-(intStart+1));
	int intPos1=strLeft.Find("=");
	strValue1=strLeft.Right(strLeft.GetLength()-(intPos1+1));
	int intPos2=strRight.Find("=");
	strValue2=strRight.Right(strRight.GetLength()-(intPos2+1));
	_tcscpy(value1,strValue1.GetBuffer());
	_tcscpy(value2,strValue2.GetBuffer());
	return mark;
}

int COperateFunc::InputMessage(char* key,char* message,char* unit)
{
    CMessageInput m_messageInput((CString)key,(CString)message,(CString)unit,0);
	m_messageInput.DoModal();
	return 1;
}

COperateFunc::~COperateFunc(void)
{
}



int COperateFunc::ResultDecide(char* result)
{
	CMessageDecide aDlg;
    if (aDlg.DoModal() == 1)
    {
		strcpy(result,"1");
    }
	else
	{
		strcpy(result,"0");
	}
	return 0;
}

int COperateFunc::ReadSampleSet(char* item, char* waittime, char* count, char* interval)
{

	//m_strTestConfig     保存了配置文件路径
	char m_tempTestconfig[MAX_PATH];
	_tcscpy(m_tempTestconfig,m_strTestConfig);
	char s[MAX_PATH];	
	(_tcsrchr(m_tempTestconfig,_T('\\')))[1] = 0;  //去掉testconfi.ini文件
	_tcscpy(s,m_tempTestconfig);
	CString s_temp(s);
	s_temp+="UNI-T UT181A SampleConfig.ini";
	//AfxMessageBox(s_temp);
	int mark=GetPrivateProfileString(item,"Count","Error",count,50,s_temp);       //从Ini文件中取采样次数
	mark=GetPrivateProfileString(item,"IntervalTime","Error",interval,50,s_temp);       //从Ini文件中取采样间隔时间
	mark=GetPrivateProfileString(item,"WaitTime","Error",waittime,50,s_temp);
	return mark;
}

int COperateFunc::ResultCorrection(char* resultStr,char* digit,char* offset,char* result)
{
	int digitNum=atoi(digit);
	float offsetValue=atof(offset);
	float tempValue=0;

	char* split=",";
	char* p;

	p=strtok(resultStr,split);

	if((p[1]<='9'&&p[1]>='0')||(p[1]=='.'))
	{
		tempValue=atof(p)-offsetValue;
		sprintf(result,"%.*lf",digitNum,tempValue);
	}
	else
		sprintf(result,"%s",p);

	for(p=strtok(NULL,split);p!=NULL;p=strtok(NULL,split)){		
		if((p[1]<='9'&&p[1]>='0')||(p[1]=='.'))
		{
			tempValue=atof(p)-offsetValue;
			sprintf(result,"%s,%.*lf",result,digitNum,tempValue);
		}
		else
			sprintf(result,"%s,%s",result,p);

	}
	return 0;
}

int COperateFunc::ChannelCalibration_M(char* resultStr, char* mode, char* result)
{
	char m_tempTestconfig[MAX_PATH];
	_tcscpy(m_tempTestconfig,m_strTestConfig);
	char s[MAX_PATH];	
	(_tcsrchr(m_tempTestconfig,_T('\\')))[1] = 0;  //去掉testconfi.ini文件
	_tcscpy(s,m_tempTestconfig);
	CString s_temp(s);
	s_temp+="UNI-T Channel Calibration.ini";
	
	char* split=",";
	char* p;
	int k=2; 
	char channel[10];
	float tempValue=0;
	char calValue[50];
	
	p=strtok(resultStr,split);
	if((p[1]<='9'&&p[1]>='0')||(p[1]=='.'))
	{
		GetPrivateProfileString(mode,"CH1","0",calValue,50,s_temp);
		tempValue=atof(p)-atof(calValue);
		sprintf(result,"%f",tempValue);
	}
	else
		sprintf(result,"%s",p);

	for(p=strtok(NULL,split);p!=NULL;p=strtok(NULL,split)){		
		if((p[1]<='9'&&p[1]>='0')||(p[1]=='.'))
		{
			sprintf(channel,"CH%d",k);
			GetPrivateProfileString(mode,channel,"0",calValue,50,s_temp);
			tempValue=atof(p)-atof(calValue);
			sprintf(result,"%s,%f",result,tempValue);
		}
		else
			sprintf(result,"%s,%s",result,p);
		k++;
	}
	return 0;
}
