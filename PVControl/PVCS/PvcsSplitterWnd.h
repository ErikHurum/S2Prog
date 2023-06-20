#pragma once


// CPvcsSplitterWnd

class CPvcsSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CPvcsSplitterWnd)

public:
	CPvcsSplitterWnd();
	virtual ~CPvcsSplitterWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void ActivateTank(const int& param_iTankID);
};


