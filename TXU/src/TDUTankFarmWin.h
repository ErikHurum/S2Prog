#pragma once
//#include "tdupresentwin.h"

class TDUTankFarmWin :
	public TDUGroupWin
{
private:
	static const TDUValueTable DefaultCWValues[TDU_WIN_COL];
public:
	TDUTankFarmWin(void);
	~TDUTankFarmWin(void);
	void AppSetup(void);
	void PrintReport(int PrinterId);
};
