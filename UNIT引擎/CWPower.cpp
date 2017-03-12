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
	TestInit,  //初始化
	UUTSet,   //被测设备设置
	ATESet,  //测试设备设置
	DataRead, //读取测试数据
	Finished  //结束

};

/*********************************功率测试***************************************/
int _stdcall TestFunction(
								char* LuaFilePath, //Lua文件路径
								char* uutCom,   //被测设备物理地址， 
								char* testSet, //测试参数设置
								char* configPath, //测试配置文件路径
								int testSerial, //测试顺序号
								int testMode, //测试模式0=自动 1=半自动
								char* testValue,
								int num,
								char *ipAddr,
								char *rf,
								char *vsg,
								char *rout
								)
{
	COperateFunc::m_strTestConfig=configPath;//测试配置文件路径
	char err[100];
	char* pt1=new char[255];
	try
	{
		ShareMemory myShare(1000);
	    myShare.CreatSharedMemory(); //进程共享内存申请
		COperateFunc myOpe;
		//CDigMeter myMeter("DigMeter",myShare);
		//CDigSource mySource("DigSource",myShare);

		char uutPath[MAX_PATH];
		_tcscpy(uutPath,LuaFilePath);   //_tcscpy代表strcpy  ，将Lua文件路径复制到uutPath变量
	    (_tcsrchr(uutPath,_T('\\')))[0] = 0;
	    (_tcsrchr(uutPath,_T('\\')))[1] = 0;


		lua_State *L=lua_open();	//Lua解释器指针， 建立lua栈用于和C交互 luaopen_base(lua_State*L) 打开基本函数库

		//注册变量到LUA环境
		RegisterToLua registerToLua(L); //构造类对象
		registerToLua.RegisterFuncToLua();  
		lua_tinker::set(L, "myShare", &myShare);   //tinker 提供的 lua与 C++ 函数的相关接口函数 ，这样便可以屏蔽底层函数
		lua_tinker::set(L, "myOpe",  &myOpe); //向栈中倒入变量
		lua_tinker::set(L, "myUUTPath", uutPath);
		lua_tinker::set(L, "myIP", ipAddr);
		lua_tinker::set(L, "myRF", rf);
		lua_tinker::set(L, "myVSG", vsg);
		lua_tinker::set(L, "myROUT", rout);

		luaL_openlibs(L);// 运行脚本 
		CString str;
		str.Format("%s",LuaFilePath);
		AfxMessageBox(str);


		// 装载lua文件
		lua_tinker::dofile(L,LuaFilePath);     
		//回调lua中函数
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
		//释放
		lua_close(L);  //关闭栈
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
