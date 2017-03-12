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
	hFileMap=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,nSize,"ATSSharedMemory");// ���������ڴ�飬ATSSharedMemory�ļ�ӳ����������
	if(hFileMap==NULL||hFileMap==INVALID_HANDLE_VALUE)	// ��������
		return 0;
	if (GetLastError() == ERROR_ALREADY_EXISTS)			// �����ڴ��Ѿ�����
	{
		hFileMap=OpenFileMapping(FILE_MAP_WRITE,false,"ATSSharedMemory");  //��һ���ֳɵ��ļ�ӳ�����ATSSharedMemory
		return 1;
	}
	return 2;
}

int ShareMemory::CreatSharedMemory_Any(char* shareName)
{
	hFileMap=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,nSize,shareName);// ���������ڴ��
	if(hFileMap==NULL||hFileMap==INVALID_HANDLE_VALUE)	// ��������
		return 0;
	if (GetLastError() == ERROR_ALREADY_EXISTS)			// �����ڴ��Ѿ�����
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

	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_READ,0,0,0);	// ���ļ�ӳ��������ͼӳ�����ַ�ռ䣬ͬʱ�õ���ӳ����ͼ���׵�ַ
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
	//�������ڹ����ڴ�����м����־����
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

	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_WRITE,0,0,nSize);	// ���ļ�ӳ��������ͼӳ�����ַ�ռ䣬ͬʱ�õ���ӳ����ͼ���׵�ַ
	if(lpMap==NULL)				// ӳ�����
	{
		delete[] szBuffer;
		return 0;
	}
	memset(lpMap, 0, nSize);	// ��չ����ڴ�
	memcpy(lpMap,szBuffer,nSize);	// ������д�빲���ڴ�
	//memcpy(lpMap,szFormat,strTemp.GetLength()+1);	// ������д�빲���ڴ�
	Sleep(50);
	UnmapViewOfFile(lpMap);		//��ӳ��������ڴ��ļ�ӳ�������ͼж��
	delete[] szBuffer;
	return 1;
}

int ShareMemory::WriteToSharedMemory_1(char* pData)
{

	//�������ڹ����ڴ�����м����־����
	CString strTemp;
	strTemp.Format(">>>%s",pData);
	pData=(char*)(LPCTSTR)strTemp;
	//////////////////////////////////////////////////////
	if(hFileMap==NULL)
		return 0;

	LPVOID lpMap=MapViewOfFile(hFileMap,FILE_MAP_WRITE,0,0,nSize);	// ���ļ�ӳ��������ͼӳ�����ַ�ռ䣬ͬʱ�õ���ӳ����ͼ���׵�ַ
	if(lpMap==NULL)				// ӳ�����
	{
		return 0;
	}
	Sleep(100);
	memset(lpMap,0, nSize);	// ��չ����ڴ�
	memcpy(lpMap,pData,strTemp.GetLength()+1);	// ������д�빲���ڴ�
	Sleep(100);
	UnmapViewOfFile(lpMap);		//��ӳ��������ڴ��ļ�ӳ�������ͼж��
	return 1;
}

int ShareMemory::ReleaseSharedMemory()
{
	if(hFileMap!=NULL)
    	CloseHandle(hFileMap);		// �رչ����ڴ�
	return 1;
}
ShareMemory::~ShareMemory(void)
{
}