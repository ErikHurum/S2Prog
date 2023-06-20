#pragma once


// CPvcsSplitterLowerWnd

class CPvcsSplitterLowerWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CPvcsSplitterLowerWnd)

public:
	CPvcsSplitterLowerWnd();
	virtual ~CPvcsSplitterLowerWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


