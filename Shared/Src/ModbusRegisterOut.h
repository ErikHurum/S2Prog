#pragma once
#ifndef ModbusRegisterOuth
#define ModbusRegisterOuth

class ModbusRegisterOut:public ModbusRegister {
public:
	static set<PRogramObjectBase*>ModbusSet;
	ModbusRegisterOut(bool pIsCreatedFromMultiple=false, int ModuleType=C_PRO_MODBUS_REG_OUT, bool InsertInSet=true);
	~ModbusRegisterOut();
	int   GetOutputVal(void);
	float GetOutputValFloat(void);
    AnsiString GetOutputString(void);
	void  CalculateScale(void);
	void  Update(void);
    ModbusRegisterOut& operator=(ModbusRegisterOut Src);
	void UpdateFromMultiple(unsigned pIdNumber, int pChannel);
	virtual AnsiString GetRegisterValue(void);
    virtual void SetProList(void);

};
#endif
