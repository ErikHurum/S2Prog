#pragma once
//#include "tdupresentwin.h"

class TDUCargoWin :
	public TDUGroupWin
{
private:
	static const TDUValueTable DefaultCWValues[TDU_WIN_COL];
public:
	TDUCargoWin(void);
	~TDUCargoWin(void);
	void AppSetup(void);
	void PrintReport(int PrinterId);
};
