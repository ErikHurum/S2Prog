#pragma once

class TDUPresentWin:public TDUBasicWin {
public:
	TDUPresentWin(void);
	~TDUPresentWin(void);
	int PWinXSize;
	int PWinYSize;
	int ExtraSize;
	TDUPresentWin *MyPtr;
	virtual void SetButton(void);
	virtual void Paintnew(void);

	virtual void cbEventHandler(WM_MESSAGE* pMsg);

};
