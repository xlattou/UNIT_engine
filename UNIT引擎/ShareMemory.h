#pragma once

class ShareMemory
{
public:
	ShareMemory(int n);
	ShareMemory();
	int CreatSharedMemory();								// ���������ڴ��
	int CreatSharedMemory_Any(char* shareName);								// ���������ڴ��
	int ReadSharedMemory(char* shareName,char* shareValue);								// ���������ڴ��
	int WriteToSharedMemory(const char *szFormat,...);	// ������д�빲���ڴ�
	int WriteToSharedMemory_1(char* pData);	// ������д�빲���ڴ�
	int ReleaseSharedMemory();						// �رչ����ڴ�
	~ShareMemory(void);
	HANDLE hFileMap;
private:
	int nSize;
};