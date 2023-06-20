#pragma once
#ifndef ModbusWago487RegisterInh
#define ModbusWago487RegisterInh
class ModbusWago487RegisterIn:public ModbusRegisterIn {
public:
	ModbusWago487RegisterIn(bool pIsCreatedFromMultiple=false);
	~ModbusWago487RegisterIn();
	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	void Update(void);
    AnsiString GetRegisterType(void);
};
#endif
