//---------------------------------------------------------------------------
#ifndef ModbusCoilH
#define ModbusCoilH
class ModbusCoil:public ModbusObject{
protected:
	int AlarmDelay;
    int NormalState;
public:
	static set<PRogramObjectBase*>ModbusSet;
	ModbusCoil(void);
	~ModbusCoil(void);
// Routines for the Configuration
	virtual AnsiString MakeConfigString(int ExtraTabs=0)=0;
	virtual bool LoadConfigString(TSNConfigString &ConfigString)=0;
	virtual void Update(void)=0;
	int GetAlarmDelay(void);

};
//---------------------------------------------------------------------------
#endif

