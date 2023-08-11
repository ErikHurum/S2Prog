#pragma once

class TDUTankPressWin :
public TDUGroupWin {
private:
	static const TDUValueTable DefaultCWValues[TDU_WIN_COL];
public:
	TDUTankPressWin(void);
	~TDUTankPressWin(void);
	void AppSetup(void);
	void PrintReport(int PrinterId);

};
