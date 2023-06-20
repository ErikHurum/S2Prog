#pragma once
#ifndef ModbusCoilOuth
#define ModbusCoilOuth
class ModbusCoilOut:public ModbusCoil {
private:
    int CurrentState;
	int NormalState;
	int DeactivateBy;
    clock_t ActivatedTime;
    int PulseTime;
    bool SetToNormal;
    int   ValueKey;
	set<PRogramObject*>PROList;
	set<AlarmBasic*>AlarmList;
	int AlarmAlternative;
	vector<int>AlarmTypeList;
	vector<unsigned>IdNumbers;
    PRogramObject *SingleObject;
public:
	static set<PRogramObjectBase*>ModbusSet;
	ModbusCoilOut(bool pIsCreatedFromMultiple=false);
	~ModbusCoilOut();
// Routines for the Configuration
	AnsiString MakeConfigString(int ExtraTabs=0);
	bool LoadConfigString(TSNConfigString &ConfigString);
	void SetAlarmList(void);
	void SetProList(void);
	int GetAlarmOutputVal(void);
	bool GetOutputVal(void);
	void Update(void);
    ModbusCoilOut& operator=(ModbusCoilOut Src);
    void UpdateFromMultiple(unsigned pIdNumber, int pChannel);
    int GetObjectId(void);
    AnsiString GetValueKey(void);
    AnsiString GetRegisterType(void);
    AnsiString GetRegisterValue(void);
};
#endif
