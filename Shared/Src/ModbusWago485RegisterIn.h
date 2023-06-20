#pragma once
#ifndef ModbusWago485RegisterInh
#define ModbusWago485RegisterInh
class ModbusWago485RegisterIn:public ModbusRegisterIn {
public:
	ModbusWago485RegisterIn(bool pIsCreatedFromMultiple=false);
	~ModbusWago485RegisterIn();
	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	void Update(void);
    AnsiString GetRegisterType(void);
};
#endif
