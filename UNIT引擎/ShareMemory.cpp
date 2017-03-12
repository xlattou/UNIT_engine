#include "stdafx.h"
#include "ShareMemory.h"

ShareMemory::ShareMemory(int n)
{
	nSize=n;
}
ShareMemory::ShareMemory()
{
}
int ShareMemory::CreatSharedMemory()
{
	hFileMap=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,nSize,"ATSSharedMemory");// 创建共享内存块，ATSSharedMemory文件映射对象的名字
	if(hFileMap==NULL||hFileMap==INVALID_HANDLE_VALUE)	// 创建错误
		return 0;
	if (GetLastError() == ERROR_ALREADY_EXISTS)			// 共享内存已经存在
	{
		hFileMap=OpenFileMapping(FILE_MAP_WRITE,false,"ATSSharedMemory");  //打开一个现成的文件映射对象ATSSharedMemory
		return 1;
	}
	return 2;
}

int ShareMemory::CreatSharedMemory_Any(char* shareName)
{
	hFileMap=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,nSize,shareName);// 创建共享内存块
	if(hFileMap==NULL||hFileMap==INVALID_HANDLE_VALUE)	// 创建错误
		return 0;
	if (GetLastError() == ERROR_ALREADY_EXISTS)			// 共享内存已经存在
	{
		hFileMap=OpenFileMapping(FILE_MAP_WRITE,false,shareName);
		return 1;
	}
	return 2;
}


int ShareMemory::ReadSharedMemory(char* shareName,char* shareValue)
{
    hFileMap=OpenFileMapping(FILE_MAP_READ,false,shareName);
	if(hFileMap==NULL)
		return 0;

	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_READ,0,0,0);	// 将文件映射对象的视图映射进地址空间，同时得到此映射视图的首地址
	if(lpMap==NULL)
		return 0;
	memset(shareValue,0,nSize);
	memcpy(shareValue,lpMap,nSize);
	Sleep(100);
	UnmapViewOfFile(lpMap);
	return 1;
}


int ShareMemory::WriteToSharedMemory(const char *szFormat,...)
{
	//新增，在共享内存变量中加入标志符号
	CString strTemp;
	strTemp.Format(">>>%s",szFormat);
	szFormat=(char*)(LPCTSTR)strTemp;
//////////////////////////////////////////////////////
	char *szBuffer=new char[nSize];
	va_list pArgs;
    va_start(pArgs, szFormat);      
    vsnprintf(szBuffer,nSize,szFormat,pArgs);       
    va_end(pArgs);
	if(hFileMap==NULL)
		return 0;

	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_WRITE,0,0,nSize);	// 将文件映射对象的视图映射进地址空间，同时得到此映射视图的首地址
	if(lpMap==NULL)				// 映射错误
	{
		delete[] szBuffer;
		return 0;
	}
	memset(lpMap, 0, nSize);	// 清空共享内存
	memcpy(lpMap,szBuffer,nSize);	// 将数据写入共享内存
	//memcpy(lpMap,szFormat,strTemp.GetLength()+1);	// 将数据写入共享内存
	Sleep(50);
	UnmapViewOfFile(lpMap);		//将映射进来的内存文件映射对象视图卸载
	delete[] szBuffer;
	return 1;
}

int ShareMemory::WriteToSharedMemory_1(char* pData)
{

	//新增，在共享内存变量中加入标志符号
	CString strTemp;
	strTemp.Format(">>>%s",pData);
	pData=(char*)(LPCTSTR)strTemp;
	//////////////////////////////////////////////////////
	if(hFileMap==NULL)
		return 0;

	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_WRITE,0,0,nSize);	// 将文件映射对象的视图映射进地址空间，同时得到此映射视图的首地址
	if(lpMap==NULL)				// 映射错误
	{
		return 0;
	}
	Sleep(100);
	memset(lpMap,0, nSize);	// 清空共享内存
	memcpy(lpMap,pData,strTemp.GetLength()+1);	// 将数据写入共享内存
	Sleep(100);
	UnmapViewOfFile(lpMap);		//将映射进来的内存文件映射对象视图卸载
	return 1;
}

int ShareMemory::ReleaseSharedMemory()
{
	if(hFileMap!=NULL)
    	CloseHandle(hFileMap);		// 关闭共享内存
	return 1;
}
ShareMemory::~ShareMemory(void)
{
}