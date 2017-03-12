// CWPower.cpp: implementation of the CCWPower class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CWPower.h"
#define MyDllAPI extern "C" _declspec(dllexport)

#include "ShareMemory.h"
//#include "RFAnalyser.h"
#include "OperateFunc.h"
//#include "AFAnalyser.h"
//#include "RFGenerator.h"
//#include "AFGenerator.h"
#include "DigMeter.h"
#include "DigSource.h"
#include "WLAN.h"

#include "RegisterToLua.h"
#include "./lua_tinker/lua_tinker.h"


enum Serial
{
	TestInit,  //��ʼ��
	UUTSet,   //�����豸����
	ATESet,  //�����豸����
	DataRead, //��ȡ��������
	Finished  //����

};

/*********************************���ʲ���***************************************/
int _stdcall TestFunction(
								char* LuaFilePath, //Lua�ļ�·��
								char* uutCom,   //�����豸�����ַ�� 
								char* testSet, //���Բ�������
								char* configPath, //���������ļ�·��
								int testSerial, //����˳���
								int testMode, //����ģʽ0=�Զ� 1=���Զ�
								char* testValue,
								int num,
								char *ipAddr,
								char *rf,
								char *vsg,
								char *rout
								)
{
	COperateFunc::m_strTestConfig=configPath;//���������ļ�·��
	char err[100];
	char* pt1=new char[255];
	try
	{
		ShareMemory myShare(1000);
	    myShare.CreatSharedMemory(); //���̹����ڴ�����
		COperateFunc myOpe;
		//CDigMeter myMeter("DigMeter",myShare);
		//CDigSource mySource("DigSource",myShare);

		char uutPath[MAX_PATH];
		_tcscpy(uutPath,LuaFilePath);   //_tcscpy����strcpy  ����Lua�ļ�·�����Ƶ�uutPath����
	    (_tcsrchr(uutPath,_T('\\')))[0] = 0;
	    (_tcsrchr(uutPath,_T('\\')))[1] = 0;


		lua_State *L=lua_open();	//Lua������ָ�룬 ����luaջ���ں�C���� luaopen_base(lua_State*L) �򿪻���������

		//ע�������LUA����
		RegisterToLua registerToLua(L); //���������
		registerToLua.RegisterFuncToLua();  
		lua_tinker::set(L, "myShare", &myShare);   //tinker �ṩ�� lua�� C++ ��������ؽӿں��� ��������������εײ㺯��
		lua_tinker::set(L, "myOpe",  &myOpe); //��ջ�е������
		lua_tinker::set(L, "myUUTPath", uutPath);
		lua_tinker::set(L, "myIP", ipAddr);
		lua_tinker::set(L, "myRF", rf);
		lua_tinker::set(L, "myVSG", vsg);
		lua_tinker::set(L, "myROUT", rout);

		luaL_openlibs(L);// ���нű� 
		CString str;
		str.Format("%s",LuaFilePath);
		AfxMessageBox(str);


		// װ��lua�ļ�
		lua_tinker::dofile(L,LuaFilePath);     
		//�ص�lua�к���
		pt1= lua_tinker::call<char*>(L, "TestProg",uutCom,testSet,testSerial,testMode);
		if(pt1==NULL)
		{
	    	strcpy_s(testValue,num,"Invalid");
			lua_close(L);
	    	delete[] pt1;
	     	return 1;
		}
		strcpy(testValue,pt1);
		strcpy_s(testValue,num,pt1);
		//�ͷ�
		lua_close(L);  //�ر�ջ
	}
	catch(string& e)
	{
		delete[] pt1;
		MessageBox(0,e.c_str(),"Error",0);

		return 0;
	}
	catch (CMemoryException* e)
	{
		delete[] pt1;
		e->GetErrorMessage(err,100,0);
		MessageBox(0,err,"Error",0);
		
	}
	catch (CFileException* e)
	{
		delete[] pt1;
		e->GetErrorMessage(err,100,0);
		MessageBox(0,err,"Error",0);
	}
	catch (CException* e)
	{
		delete[] pt1;
		e->GetErrorMessage(err,100,0);
		MessageBox(0,err,"Error",0);
	}
	return 1;
}
