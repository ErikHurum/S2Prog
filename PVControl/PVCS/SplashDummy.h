#pragma once


// CSplashDummy

class CSplashDummy : public CWnd
{
	DECLARE_DYNAMIC(CSplashDummy)

public:
	CSplashDummy();
	virtual ~CSplashDummy();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
private:
	int m_nSec;
public:
	int m_nSecLeft;
	void Draw(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


