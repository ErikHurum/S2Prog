#pragma once

class TDUVoidSpaceWin :
	public TDUGroupWin
{
private:
	static const TDUValueTable DefaultCWValues[TDU_WIN_COL];
public:
	TDUVoidSpaceWin(void);
	~TDUVoidSpaceWin(void);
	void AppSetup(void);
	void PrintReport(int PrinterId);
};
