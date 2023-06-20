#pragma once
#ifndef ModbusMultipleh
#define ModbusMultipleh
class ModbusMultiple:public PRogramObjectBase {
private:
    int NumberOfCopies;
    int RegisterStepsIn ;
    int RegisterStepsOut ;
    int CoilStepsIn     ;
    int CoilStepsOut     ;
	vector<ModbusObject*>ModbusObectVector;

public:
    static set<PRogramObjectBase*>ModbusSet;
	vector<unsigned>IdNumbers;
	set<unsigned>IgnoreIdNumbers;

    ModbusMultiple();
    ~ModbusMultiple();
    AnsiString MakeConfigString(int ExtraTabs=0);
    bool LoadConfigString(TSNConfigString &ConfigString);
    static set<PRogramObjectBase*> GetModbusObjectSet(void);

};
#endif
