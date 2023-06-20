#pragma once
#ifndef ModbusWago482RegisterInh
#define ModbusWago482RegisterInh
class ModbusWago482RegisterIn:public ModbusRegisterIn {
public:
	ModbusWago482RegisterIn(bool pIsCreatedFromMultiple=false);
	~ModbusWago482RegisterIn();
	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	void Update(void);
    AnsiString GetRegisterType(void);
};
#endif
