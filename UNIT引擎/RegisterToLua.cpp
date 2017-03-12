#include "stdafx.h"
#include "RegisterToLua.h"
#include "./lua_tinker/lua_tinker.h"
#include "ShareMemory.h"
#include "OperateFunc.h"
#include "FuncHelper.h"
#include "Switch.h"
#include "WLAN.h"
#include "Spectrum.h"
#include "SpectrumdigModeSet.h"
#include "SignalGen.h"


RegisterToLua::RegisterToLua(lua_State* L)
{
	luaState = L;  //初始化LUA环境
}

/*****************注册C++类到LUA环境***********************************/
int RegisterToLua::RegisterFuncToLua()
{
	
	try
	{
    	RegisterDigMeter(); //数字多用表
		RegisterMultimeter();
    	RegisterDigSource(); //数字校准源
    	RegisterOperateFunc();
    	RegisterShareMemory();
    	RegisterSwitch();
    	RegisterFuncHelper();
		RegisterSpectrum();   //频谱
		RegisterFuncWLAN();  //WLAN综测仪
		RegisterFuncSignalGen();
		RegisterFuncSpectumdigModeSet();  //
	}
	catch(string &e)
	{
		throw string("RegisterToLua Failure!");
		return 0;
	}

	return 1;
}


/****************注册OperateFunc类到LUA环境***********************************/
int RegisterToLua::RegisterOperateFunc()
{
	try
	{
    	luaopen_base(luaState);
    	luaopen_string(luaState);
    	luaopen_math(luaState);
    	luaopen_os(luaState);
    	luaL_openlibs(luaState);
 
    	lua_tinker::class_add<COperateFunc>(luaState, "OperateFunc");
        lua_tinker::class_con<COperateFunc>(luaState,lua_tinker::constructor<void>()); //构造函数
        lua_tinker::class_def<COperateFunc>(luaState, "GetFunc", &COperateFunc::GetFunc);
    	lua_tinker::class_def<COperateFunc>(luaState, "GetRunStatus", &COperateFunc::GetRunStatus); 
    	lua_tinker::class_def<COperateFunc>(luaState, "StringSplit", &COperateFunc::StringSplit); 
		lua_tinker::class_def<COperateFunc>(luaState, "WriteStatusCache", &COperateFunc::WriteStatusCache); 
    	lua_tinker::class_def<COperateFunc>(luaState, "ReadStatusCache", &COperateFunc::ReadStatusCache); 
		lua_tinker::class_def<COperateFunc>(luaState, "InputMessage", &COperateFunc::InputMessage);
		lua_tinker::class_def<COperateFunc>(luaState, "ShowMessage", &COperateFunc::ShowMessage); 
		lua_tinker::class_def<COperateFunc>(luaState, "ResultDecide", &COperateFunc::ResultDecide); 
		lua_tinker::class_def<COperateFunc>(luaState, "ReadSampleSet", &COperateFunc::ReadSampleSet); 
		lua_tinker::class_def<COperateFunc>(luaState, "ResultCorrection", &COperateFunc::ResultCorrection);
		lua_tinker::class_def<COperateFunc>(luaState, "ChannelCalibration_M", &COperateFunc::ChannelCalibration_M);
		
	}
	catch(string &e)
	{
		throw string("RegisterOperateFunc Failure!");
		return 0;
	}
	return 1;
}

/*****************注册DigMeter类到LUA环境***********************************/

int RegisterToLua::RegisterDigMeter()
{
	try
	{
    	luaopen_base(luaState);
    	luaopen_string(luaState);
    	luaopen_math(luaState);
    	luaopen_os(luaState);
    	luaL_openlibs(luaState);

        lua_tinker::class_add<CDigMeter>(luaState, "DigMeter");
    	lua_tinker::class_con<CDigMeter>(luaState,lua_tinker::constructor<char*,ShareMemory>()); 
    	lua_tinker::class_def<CDigMeter>(luaState,"DigMeterInit",&CDigMeter::DigMeterInit);
    	lua_tinker::class_def<CDigMeter>(luaState,"DigMeterClose",&CDigMeter::DigMeterClose);
    	lua_tinker::class_def<CDigMeter>(luaState,"DigMeterConfig",&CDigMeter::DigMeterConfig);  
		lua_tinker::class_def<CDigMeter>(luaState,"DigMeterAutoZero",&CDigMeter::DigMeterAutoZero);  
		lua_tinker::class_def<CDigMeter>(luaState,"DigMeterCal",&CDigMeter::DigMeterCal); 
		lua_tinker::class_def<CDigMeter>(luaState,"DigMeterCalSave",&CDigMeter::DigMeterCalSave); 
    	lua_tinker::class_def<CDigMeter>(luaState,"DigMeterRead",&CDigMeter::DigMeterRead);
		lua_tinker::class_def<CDigMeter>(luaState,"DigMeterReadData",&CDigMeter::DigMeterReadData);
		lua_tinker::class_def<CDigMeter>(luaState,"DigMeterConfig_M",&CDigMeter::DigMeterConfig_M);  
		lua_tinker::class_def<CDigMeter>(luaState,"DigMeterRead_M",&CDigMeter::DigMeterRead_M);
	}
	catch(string &e)
	{
		throw string("Register DigMeter Failure!");
		return 0;
	}
	return 1;
}

/*****************注册Multimeter类到LUA环境***********************************/

int RegisterToLua::RegisterMultimeter()
{
	try
	{
    	luaopen_base(luaState);
    	luaopen_string(luaState);
    	luaopen_math(luaState);
    	luaopen_os(luaState);
    	luaL_openlibs(luaState);

        lua_tinker::class_add<CMultimeter>(luaState, "Multimeter");
    	lua_tinker::class_con<CMultimeter>(luaState,lua_tinker::constructor<char*,ShareMemory>()); 
        lua_tinker::class_def<CMultimeter>(luaState,"MultiNumbers",&CMultimeter::MultiNumbers);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiQueryResult",&CMultimeter::MultiQueryResult);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiConnect",&CMultimeter::MultiConnect);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiDisconnect",&CMultimeter::MultiDisconnect);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiRangeSet",&CMultimeter::MultiRangeSet);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiMeasFuncSet",&CMultimeter::MultiMeasFuncSet);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiReadResult",&CMultimeter::MultiReadResult);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiInit",&CMultimeter::MultiInit);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiClose",&CMultimeter::MultiClose);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiReadSampleResult",&CMultimeter::MultiReadSampleResult);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiReadSampleResult_M",&CMultimeter::MultiReadSampleResult_M);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiInvalidValue",&CMultimeter::MultiInvalidValue);
		lua_tinker::class_def<CMultimeter>(luaState,"MultiRemoveMisuse",&CMultimeter::MultiRemoveMisuse);
	}
	catch(string &e)
	{
		throw string("Register Multimeter Failure!");
		return 0;
	}
	return 1;
}
/*****************注册DigSource类到LUA环境***********************************/

int RegisterToLua::RegisterDigSource()
{
	try
	{
		luaopen_base(luaState);
		luaopen_string(luaState);
		luaopen_math(luaState);
		luaopen_os(luaState);
		luaL_openlibs(luaState);

		lua_tinker::class_add<CDigSource>(luaState, "DigSource");
		lua_tinker::class_con<CDigSource>(luaState,lua_tinker::constructor<char*,ShareMemory>()); 
		lua_tinker::class_def<CDigSource>(luaState,"DigSourceInit",&CDigSource::DigSourceInit);
		lua_tinker::class_def<CDigSource>(luaState,"DigSourceClose",&CDigSource::DigSourceClose);
		lua_tinker::class_def<CDigSource>(luaState,"DigSourceConfig",&CDigSource::DigSourceConfig);
		lua_tinker::class_def<CDigSource>(luaState,"DigSourceOutSet",&CDigSource::DigSourceOutSet);
		lua_tinker::class_def<CDigSource>(luaState,"DigSourceOffset",&CDigSource::DigSourceOffset);
		lua_tinker::class_def<CDigSource>(luaState,"DigSourceWaveSet",&CDigSource::DigSourceWaveSet);
		lua_tinker::class_def<CDigSource>(luaState,"DigSourceReset",&CDigSource::DigSourceReset);
	}
	catch(string &e)
	{
		throw string("Register DigSource Failure!");
		return 0;
	}
	return 1;

}

/*****************注册ShareMemory类到LUA环境***********************************/
int RegisterToLua::RegisterShareMemory()
{	
	
	try
	{
    	luaopen_base(luaState);
    	luaopen_string(luaState);
    	luaopen_math(luaState);
    	luaopen_os(luaState);
    	luaL_openlibs(luaState);

        lua_tinker::class_add<ShareMemory>(luaState, "ShareMemory");
        lua_tinker::class_con<ShareMemory>(luaState,lua_tinker::constructor<int>()); //构造函数
    	lua_tinker::class_def<ShareMemory>(luaState, "CreatSharedMemory", &ShareMemory::CreatSharedMemory);
    	lua_tinker::class_def<ShareMemory>(luaState, "WriteToSharedMemory", &ShareMemory::WriteToSharedMemory_1);
    	lua_tinker::class_def<ShareMemory>(luaState, "ReleaseSharedMemory", &ShareMemory::ReleaseSharedMemory);
	}
	catch(string &e)
	{
		throw string("RegisterShareMemory Failure!");
		return 0;
	}	
	return 1;
}

/*****************注册Switch类到LUA环境***********************************/
int RegisterToLua::RegisterSwitch()
{	
	try
	{
    	luaopen_base(luaState);
    	luaopen_string(luaState);
    	luaopen_math(luaState);
    	luaopen_os(luaState);
    	luaL_openlibs(luaState);

    	lua_tinker::class_add<Switch>(luaState, "Switch");
        lua_tinker::class_con<Switch>(luaState,lua_tinker::constructor<char*,ShareMemory&>()); 
    	lua_tinker::class_def<Switch>(luaState, "SwitchSet", &Switch::SwitchSet); //开关设置
		lua_tinker::class_def<Switch>(luaState, "SwitchTemperature", &Switch::SwitchTemperature); //获取温度设置
	}
	catch(string &e)
	{
		throw string("RegisterSwitch Failure!");
		return 0;
	}
	return 1;

}

/*****************注册LuaFuncHelper类到LUA环境***********************************/
int RegisterToLua::RegisterFuncHelper()
{
  try
	{
    	luaopen_base(luaState);
    	luaopen_string(luaState);
    	luaopen_math(luaState);
    	luaopen_os(luaState);
    	luaL_openlibs(luaState);

    	lua_tinker::class_add<FuncHelper>(luaState, "FuncHelper"); 
        lua_tinker::class_con<FuncHelper>(luaState,lua_tinker::constructor<void>()); //构造函数
    	lua_tinker::class_def<FuncHelper>(luaState, "SleepToLua", &FuncHelper::SleepToLua);
    	lua_tinker::class_def<FuncHelper>(luaState, "GetTickCountToLua", &FuncHelper::GetTickCountToLua);
	}
	catch(string &e)
	{
		throw string("RegisterFuncHelper Failure!");
		return 0;
	}
	return 1;
}


/*****************注册频谱类到LUA环境***********************************/
int RegisterToLua::RegisterSpectrum()
{
	try
	{
		luaopen_base(luaState);
		luaopen_string(luaState);
		luaopen_math(luaState);
		luaopen_os(luaState);
		luaL_openlibs(luaState);   

		lua_tinker::class_add<CSpectrum>(luaState, "Spectrum");
		lua_tinker::class_con<CSpectrum>(luaState,lua_tinker::constructor<char*,ShareMemory>()); 
		lua_tinker::class_def<CSpectrum>(luaState,"SpecInit",&CSpectrum::SpecInit);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecClose",&CSpectrum::SpecClose);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecContinuous",&CSpectrum::SpecContinuous);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecRefLevelConfig",&CSpectrum::SpecRefLevelConfig);  
		lua_tinker::class_def<CSpectrum>(luaState,"SpecFreqConfig",&CSpectrum::SpecFreqConfig);  
		lua_tinker::class_def<CSpectrum>(luaState,"SpecSpanConfig",&CSpectrum::SpecSpanConfig); 
		lua_tinker::class_def<CSpectrum>(luaState,"SpecSweepConfig",&CSpectrum::SpecSweepConfig);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecBandWidthConfig",&CSpectrum::SpecBandWidthConfig);  
		lua_tinker::class_def<CSpectrum>(luaState,"SpecActiveMarker",&CSpectrum::SpecActiveMarker);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecMoveMarker",&CSpectrum::SpecMoveMarker); 
		lua_tinker::class_def<CSpectrum>(luaState,"SpecGetMarkerLevel",&CSpectrum::SpecGetMarkerLevel);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecGetMarkerFreq",&CSpectrum::SpecGetMarkerFreq);  
		lua_tinker::class_def<CSpectrum>(luaState,"SpecGetWave",&CSpectrum::SpecGetWave);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecAttenConfig",&CSpectrum::SpecAttenConfig);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecDetectorConfig",&CSpectrum::SpecDetectorConfig);  
		lua_tinker::class_def<CSpectrum>(luaState,"SpecTraceModeConfig",&CSpectrum::SpecTraceModeConfig);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecAllMarkerOff",&CSpectrum::SpecAllMarkerOff); 
		lua_tinker::class_def<CSpectrum>(luaState,"SpecAllDeltaMarkerOff",&CSpectrum::SpecAllDeltaMarkerOff);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecDeltaMarkerConfig",&CSpectrum::SpecDeltaMarkerConfig);  
		lua_tinker::class_def<CSpectrum>(luaState,"SpecSetLimitLine",&CSpectrum::SpecSetLimitLine);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecReadFileFromIns",&CSpectrum::SpecReadFileFromIns); 
		lua_tinker::class_def<CSpectrum>(luaState,"SpecHardcopyToFile",&CSpectrum::SpecHardcopyToFile);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecAmpConfig",&CSpectrum::SpecAmpConfig);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecRBWTest",&CSpectrum::SpecRBWTest);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecRBWTestM",&CSpectrum::SpecRBWTestM);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecMarkerCount",&CSpectrum::SpecMarkerCount);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecGetMarkerCount",&CSpectrum::SpecGetMarkerCount);
		lua_tinker::class_def<CSpectrum>(luaState,"SpecInputCoupleSet",&CSpectrum::SpecInputCoupleSet);
		lua_tinker::class_def<CSpectrum>(luaState,"ReceiverPreAmpConfig",&CSpectrum::ReceiverPreAmpConfig);
	}
	catch(string &e)
	{
		throw string("Register Spectrum Failure!");
		return 0;
	}
	return 1;
}

/*****************注册CWLAN类到LUA环境***********************************/
int RegisterToLua::RegisterFuncWLAN()
{
	try
	{
		luaopen_base(luaState);
		luaopen_string(luaState);
		luaopen_math(luaState);
		luaopen_os(luaState);
		luaL_openlibs(luaState);

		lua_tinker::class_add<CWLAN>(luaState, "CWLAN"); 
		lua_tinker::class_con<CWLAN>(luaState,lua_tinker::constructor<char*,ShareMemory>()); //构造函数
		lua_tinker::class_def<CWLAN>(luaState, "RegRFFreLev", &CWLAN:: RegRFFreLev);
		lua_tinker::class_def<CWLAN>(luaState, "RegIQ3140RFFreLevVsg", &CWLAN::RegIQ3140RFFreLevVsg);
		lua_tinker::class_def<CWLAN>(luaState, "RegParamSetting", &CWLAN::RegParamSetting);
		lua_tinker::class_def<CWLAN>(luaState, "RegIQ3140RFFreLevVsa", &CWLAN::RegIQ3140RFFreLevVsa);
		lua_tinker::class_def<CWLAN>(luaState, "RegIQ2200RFFreLevVsg", &CWLAN::RegIQ2200RFFreLevVsg);
		lua_tinker::class_def<CWLAN>(luaState, "RegIQ2200RFFreLevVsa", &CWLAN::RegIQ2200RFFreLevVsa);
		
	}
	catch(string &e)
	{
		throw string("RegisterFuncWLAN Failure!");
		return 0;
	}
	return 1;
}

/*****************注册SignalGen类到LUA环境***********************************/
int RegisterToLua::RegisterFuncSignalGen()
{
	try
	{
		luaopen_base(luaState);
		luaopen_string(luaState);
		luaopen_math(luaState);
		luaopen_os(luaState);
		luaL_openlibs(luaState);

		lua_tinker::class_add<CSignalGen>(luaState, "CSignalGen"); 
		lua_tinker::class_con<CSignalGen>(luaState,lua_tinker::constructor<char*,ShareMemory>()); //构造函数
		lua_tinker::class_def<CSignalGen>(luaState, "RegGetSN", &CSignalGen:: RegGetSN);
		lua_tinker::class_def<CSignalGen>(luaState, "RegRFDigModeOutSet", &CSignalGen::RegRFDigModeOutSet);
		lua_tinker::class_def<CSignalGen>(luaState, "RegRFGenClose", &CSignalGen::RegRFGenClose);
		lua_tinker::class_def<CSignalGen>(luaState, "RegRFGenDigModeSet", &CSignalGen:: RegRFGenDigModeSet);
		lua_tinker::class_def<CSignalGen>(luaState, "RegRFGenInit", &CSignalGen::RegRFGenInit);
		lua_tinker::class_def<CSignalGen>(luaState, "RegRFGenOutSet", &CSignalGen::RegRFGenOutSet);
		lua_tinker::class_def<CSignalGen>(luaState, "RegRFGenSelectDigWave", &CSignalGen::RegRFGenSelectDigWave);
		lua_tinker::class_def<CSignalGen>(luaState, "RegRFGenSet", &CSignalGen::RegRFGenSet);
	}
	catch(string &e)
	{
		throw string("RegisterFuncSignalGen Failure!");
		return 0;
	}
	return 1;
}

/*****************注册SpectumdigModeSet类到LUA环境***********************************/
int RegisterToLua::RegisterFuncSpectumdigModeSet()
{
	try
	{
		luaopen_base(luaState);
		luaopen_string(luaState);
		luaopen_math(luaState);
		luaopen_os(luaState);
		luaL_openlibs(luaState);

		lua_tinker::class_add<CSpectrumdigModeSet>(luaState, "CSpectrumdigModeSet"); 
		lua_tinker::class_con<CSpectrumdigModeSet>(luaState,lua_tinker::constructor<char*,ShareMemory>()); //构造函数
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegSpecModeSet", &CSpectrumdigModeSet:: RegSpecModeSet);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegLTESetULink", &CSpectrumdigModeSet::RegLTESetULink);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegLTESetB10M", &CSpectrumdigModeSet::RegLTESetB10M);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegWCDMAradioMS", &CSpectrumdigModeSet:: RegWCDMAradioMS);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegGSMMeasResult", &CSpectrumdigModeSet::RegGSMMeasResult);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegLTEMeasResult", &CSpectrumdigModeSet::RegLTEMeasResult);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegCDMA2000MeasResult", &CSpectrumdigModeSet::RegCDMA2000MeasResult);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegWCDMAMeasResult", &CSpectrumdigModeSet::RegWCDMAMeasResult);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegGSMEevm", &CSpectrumdigModeSet::RegGSMEevm);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegLTEEvm", &CSpectrumdigModeSet::RegLTEEvm);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegWCDMARho", &CSpectrumdigModeSet::RegWCDMARho);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegMeasTX", &CSpectrumdigModeSet::RegMeasTX);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegModeSetupAG", &CSpectrumdigModeSet::RegModeSetupAG);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegModeSetupBG", &CSpectrumdigModeSet::RegModeSetupBG);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegModeSetupEDR", &CSpectrumdigModeSet::RegModeSetupEDR);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegModeSetupGDO", &CSpectrumdigModeSet::RegModeSetupGDO);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegWLanBTReadData", &CSpectrumdigModeSet::RegWLanBTReadData);
		lua_tinker::class_def<CSpectrumdigModeSet>(luaState, "RegMeasSetup5ms", &CSpectrumdigModeSet::RegMeasSetup5ms);

	}
	catch(string &e)
	{
		throw string("RegisterFuncCSpectumdigModeSet Failure!");
		return 0;
	}
	return 1;
}

RegisterToLua::~RegisterToLua(void)
{
}
