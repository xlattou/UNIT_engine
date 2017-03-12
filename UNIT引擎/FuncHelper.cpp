#include "StdAfx.h"
#include "FuncHelper.h"

FuncHelper::FuncHelper(void)
{
}

/*---------------------------------------------------------------------------*/ 
/*  string转换char                                                           */
/*---------------------------------------------------------------------------*/ 
void FuncHelper::strToChar(std::string s, char *result)
{
	for(int i=0;i<(int)s.length()+1;i++)
	{
		result[i]=s[i];
	}
}

/*/*---------------------------------------------------------------------------*/ 
/*  WCHAR转换string                                                          */
/*---------------------------------------------------------------------------*/ 
/*void FuncHelper::WcharToChar(WCHAR *src,char *result)
{
	WCHAR lps[256];
    _tcscpy(lps,src);
    int nLen = wcslen(src)+1;
	WideCharToMultiByte(CP_ACP,0,lps,nLen,result,2*nLen,NULL,NULL);

} */

/*---------------------------------------------------------------------------*/ 
/*  获取LUA文件路径                                                         */
/*---------------------------------------------------------------------------*/ 

void FuncHelper::GetLuaFilePath(char *DestPath,char *FileName)
{
	//获取主程序路径
	//WCHAR szDllFolder[MAX_PATH];
    char szDllFolder[MAX_PATH];
	GetModuleFileName(NULL,szDllFolder,MAX_PATH);
   (_tcsrchr(szDllFolder,_T('\\')))[1] = 0;
   
   _tcscpy(DestPath,szDllFolder);
  
   //LUA脚本文件路径获取
    std::string path(DestPath);
	std::string luaFileName(FileName);
	path += "DataBase\\LuaScript\\";
	path += luaFileName;
	path += ".lua";
	//path+="

	//string转char
	strToChar(path,DestPath);

}

void FuncHelper::SleepToLua(double n)
  {
	 
	  Sleep(n*1000);
  }

double  FuncHelper::GetTickCountToLua()
{
	double time =GetTickCount();
	time /= 1000;
	return time;
	//time /=1000;
}
FuncHelper::~FuncHelper(void)
{
}
