#ifdef MyDllAPI
#else
#define MyDllAPI extern "C" _declspec(dllexport)
#endif

MyDllAPI int _stdcall PowerTest(
								char* luaFilePath, //测试项目lua文件路径
								char* uutCom,   //被测设备物理地址， 
								char* testSet, //测试参数设置
								char* configPath, //测试配置文件路径
								int serial, //测试顺序号
								int testMode, //测试模式0=自动 1=半自动
								char* testValue,
								int num	
								);