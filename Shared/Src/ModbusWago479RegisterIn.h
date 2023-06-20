#pragma once
#ifndef ModbusWago479RegisterInh
#define ModbusWago479RegisterInh
class ModbusWago479RegisterIn:public ModbusRegisterIn {
public:
	ModbusWago479RegisterIn(bool pIsCreatedFromMultiple=false);
	~ModbusWago479RegisterIn();
	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	void Update(void);
    AnsiString GetRegisterType(void);
};
#endif
