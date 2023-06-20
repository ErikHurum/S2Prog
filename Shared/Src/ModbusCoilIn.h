#pragma once
#ifndef ModbusCoilInh
#define ModbusCoilInh
class PROLevelSwitch;

class ModbusCoilIn : public ModbusCoil {
private:
    AlarmModbusInCoil *AlarmPtr;
    PRogramObjectBase *ObjectPtr;
    int         ValueKey;
    unsigned    RefIDNumber;
    /// True if ObjectID not defined in the configuration file
    bool        DefaultId;
    bool        AutoReset;
    bool        NotInitiated;
public:
    static set<PRogramObjectBase *>ModbusSet;
    ModbusCoilIn(bool pIsCreatedFromMultiple = false);
    ~ModbusCoilIn();
    AnsiString MakeConfigString(int ExtraTabs = 0);
    bool LoadConfigString(TSNConfigString &ConfigString);
    void Update(void);
    void SetProList(void);
    ModbusCoilIn & operator=(ModbusCoilIn Src);
    void UpdateFromMultiple(unsigned pIdNumber, int pChannel);
    int GetObjectId(void);
    AnsiString GetValueKey(void);
    AnsiString GetRegisterType(void);
    AnsiString GetRegisterValue(void);
    AlarmBasic* GetAlarmPtr(void);
    void InitiateCoils(ModbusUnit *UnitPtr);
    void SetCoil(bool State);

};
#endif
