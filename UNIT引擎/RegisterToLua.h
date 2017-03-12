#pragma once
#include "DigMeter.h"
#include "DigSource.h"
#include "Multimeter.h"

class RegisterToLua
{
public:
	RegisterToLua(lua_State* L);
	//×¢²á·½·¨
	int RegisterFuncToLua();
	int RegisterDigMeter();
	int RegisterMultimeter();
	int RegisterDigSource();
	int RegisterOperateFunc();
	int RegisterShareMemory();
	int RegisterSwitch();
	int RegisterFuncHelper();
	int RegisterSpectrum();
	int RegisterFuncWLAN();
	int RegisterFuncSignalGen();
	int RegisterFuncSpectumdigModeSet();
	~RegisterToLua(void);
private:	
	lua_State* luaState;

};
