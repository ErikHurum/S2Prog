#pragma once
#ifndef ModbusCoilHistoryh
#define ModbusCoilHistoryh
class ModbusCoilHistory:public ModbusCoil {
private:
	int NormalState;
	int DeactivateBy;
	set<PRogramObject*>PROList;
	set<AlarmBasic*>AlarmList;
	int AlarmAlternative;
	vector<int>AlarmTypeList;
	vector<unsigned>IdNumbers;
	clock_t	LogTime;
public:
	static set<PRogramObjectBase*>ModbusSet;
	ModbusCoilHistory(bool pIsCreatedFromMultiple=false);
	~ModbusCoilHistory();
// Routines for the Configuration
	AnsiString MakeConfigString(int ExtraTabs=0);
	bool LoadConfigString(TSNConfigString &ConfigString);
	void SetAlarmList(void);
	void SetProList(void);
	bool GetOutputVal(void);
	void Update(void);
};
#endif
