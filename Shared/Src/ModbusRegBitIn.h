#pragma once
#ifndef ModbusRegBitInh
#define ModbusRegBitInh
class ModbusRegBitIn : public ModbusRegisterIn {
private:
    int BitOffset;
    int AlarmDelay;
    int NormalState;
    /// True if ObjectID not defined in the configuration file
    bool DefaultId;
    AlarmModbusInCoil *AlarmPtr;
    PRogramObjectBase *ObjectPtr;
    set<PRogramObject *>PROList;
    vector<unsigned>IdNumbers;
public:
    static set<PRogramObjectBase *>ModbusSet;

    ModbusRegBitIn(bool pIsCreatedFromMultiple=false);
    ~ModbusRegBitIn();
// Routines for the Configuration
    AnsiString MakeConfigString(int ExtraTabs = 0);
    bool LoadConfigString(TSNConfigString &ConfigString);
    void SetProList(void);
    void Update(void);
    ModbusRegBitIn& operator=(ModbusRegBitIn Src);
    void UpdateFromMultiple(unsigned pIdNumber, int pChannel);
    int GetObjectId(void);
	AnsiString GetRegisterType(void);
	AnsiString GetRegisterValue(void);


};
#endif
