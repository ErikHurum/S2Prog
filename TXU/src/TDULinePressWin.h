#pragma once

class TDULinePressWin :
	public TDUGroupWin
{
private:
	static const TDUValueTable DefaultCWValues[TDU_WIN_COL];
public:
	TDULinePressWin(void);
	~TDULinePressWin(void);
	void AppSetup(void);
	void PrintReport(int PrinterId);
};
