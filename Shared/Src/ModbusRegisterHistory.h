#pragma once
#ifndef ModbusRegisterHistoryh
#define ModbusRegisterHistoryh

class ModbusRegisterHistory:public ModbusRegister {
private:
	clock_t	LogTime;
public:
	static set<PRogramObjectBase*>ModbusSet;
	ModbusRegisterHistory(bool pIsCreatedFromMultiple=false);
	~ModbusRegisterHistory();
	int GetOutputVal(void);
	float GetOutputValFloat(void);
	void CalculateScale(void);
	void Update(void);
};
#endif
