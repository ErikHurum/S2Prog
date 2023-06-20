#pragma once

class TDUBallastWin :
	public TDUGroupWin
{
private:
	static const TDUValueTable DefaultCWValues[TDU_WIN_COL];
public:
	TDUBallastWin(void);
	~TDUBallastWin(void);
	void AppSetup(void);
	void PrintReport(int PrinterId);
};
