#pragma once
//#include "tdupresentwin.h"

class TDUTempWin :
	public TDUGroupWin
{
private:
	static const TDUValueTable DefaultCWValues[TDU_WIN_COL];
public:
	TDUTempWin(void);
	~TDUTempWin(void);
	void AppSetup(void);
	void PrintReport(int PrinterId);
};
