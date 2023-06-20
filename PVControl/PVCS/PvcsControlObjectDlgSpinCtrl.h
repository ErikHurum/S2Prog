#pragma once

// Class: CPvcsControlObjectDlgSpinCtrl
// Description: The Spin control to be associated with spin box used in control dialog

class CPvcsControlObjectDlgSpinCtrl : public CSpinButtonCtrl
{
	DECLARE_DYNAMIC(CPvcsControlObjectDlgSpinCtrl)

public:
	CPvcsControlObjectDlgSpinCtrl();
	virtual ~CPvcsControlObjectDlgSpinCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
};


