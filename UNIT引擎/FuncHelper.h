
#pragma once

class FuncHelper
{
public:
	FuncHelper(void);
	~FuncHelper(void);

    /*str转char*/
    void strToChar(std::string s, char *result);
	/*WCHAR转char*/
//	void FuncHelper::WcharToChar(WCHAR *src,char *result);
	/*获取LUA文件路径*/
	void GetLuaFilePath(char *DestPath,char *FileName);

	void SleepToLua(double n);
	double GetTickCountToLua(void);

};
