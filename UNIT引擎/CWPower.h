#ifdef MyDllAPI
#else
#define MyDllAPI extern "C" _declspec(dllexport)
#endif

MyDllAPI int _stdcall PowerTest(
								char* luaFilePath, //������Ŀlua�ļ�·��
								char* uutCom,   //�����豸�����ַ�� 
								char* testSet, //���Բ�������
								char* configPath, //���������ļ�·��
								int serial, //����˳���
								int testMode, //����ģʽ0=�Զ� 1=���Զ�
								char* testValue,
								int num	
								);