#pragma once
#ifndef ModbusWago473RegisterInh
#define ModbusWago473RegisterInh
class ModbusWago473RegisterIn:public ModbusRegisterIn {
public:
	ModbusWago473RegisterIn(bool pIsCreatedFromMultiple=false);
	~ModbusWago473RegisterIn();
	virtual AnsiString MakeConfigString(int ExtraTabs=0);
	void Update(void);
    AnsiString GetRegisterType(void);
};
#endif
