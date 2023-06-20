#pragma once

class TDUTempGraphWin
{
public:
	TDUTempGraphWin(void);
	~TDUTempGraphWin(void);

//	I16 aY[100];
	bool UserTouch;
	FRAMEWIN_Handle hFramWin;
	void ExecTempGraph(void);

	static void cbEventHandler(WM_MESSAGE* pMsg);

};
