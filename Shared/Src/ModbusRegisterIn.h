#pragma once
#ifndef ModbusRegisterInh
#define ModbusRegisterInh
class ModbusRegisterIn:public ModbusRegister {
private:
	bool NotInitiated;
	void CalculateScaleOut(float &ScaleOut, float &OffsetOut);
	int  GetOutputVal(void);
public:
	static set<PRogramObject*>UniquePROSet;
	static set<PRogramObjectBase*>ModbusSet;
	ModbusRegisterIn(bool pIsCreatedFromMultiple=false, int ModuleType=C_PRO_MODBUS_REG_IN, bool InsertInSet=true);
	~ModbusRegisterIn();
	void CalculateScale(void);
	float GetOutputValFloat(void);
	virtual void InitiateHoldingRegisters(ModbusUnit *UnitPtr);
	virtual void Update(void);
    ModbusRegisterIn& operator=(ModbusRegisterIn Src);
    void UpdateFromMultiple(unsigned pIdNumber, int pChannel);
	virtual AnsiString GetRegisterValue(void);
    virtual void SetProList(void);

};
#endif
