#pragma once
#include "tdupresentwin.h"

class TDUServiceWin :
	public TDUGroupWin
{
private:
	static const TDUValueTable DefaultCWValues[TDU_WIN_COL];
public:
	TDUServiceWin(void);
	~TDUServiceWin(void);
	void AppSetup(void);
	void PrintReport(int PrinterId);
};
