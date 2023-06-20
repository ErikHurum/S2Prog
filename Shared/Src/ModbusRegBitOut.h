#pragma once
#ifndef ModbusRegBitOuth
#define ModbusRegBitOuth
class ModbusRegBitOut : public ModbusRegisterOut {
private:
    int BitOffset;
    int CurrentState;
    int AlarmDelay;
    int NormalState;
    /// True if ObjectID not defined in the configuration file
 	int DeactivateBy;
	int AlarmAlternative;
    unsigned PulseTime;
    clock_t ActivatedTime;
    bool DefaultId;
    bool isVolatile;
    AlarmModbusInCoil *AlarmPtr;
    PRogramObjectBase *ObjectPtr;
    set<PRogramObject *>PROList;
	set<AlarmBasic*>AlarmList;
	vector<int>AlarmTypeList;
	vector<unsigned>IdNumbers;
public:
    static set<PRogramObjectBase *>ModbusSet;

    ModbusRegBitOut(bool pIsCreatedFromMultiple=false);
    ~ModbusRegBitOut();
// Routines for the Configuration
    AnsiString MakeConfigString(int ExtraTabs = 0);
    bool LoadConfigString(TSNConfigString &ConfigString);
	void SetAlarmList(void);
	void SetProList(void);
	int GetOutputVal(void);
	void Update(void);
    ModbusRegBitOut& operator=(ModbusRegBitOut Src);
    void UpdateFromMultiple(unsigned pIdNumber, int pChannel);
    int GetObjectId(void);
    AnsiString GetValueKey(void);
    AnsiString GetRegisterType(void);


};
#endif
