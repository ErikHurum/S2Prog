#pragma once


// CPvcsToolBarEmgButton

class CPvcsToolBarEmgButton : public CButton
{
	DECLARE_DYNAMIC(CPvcsToolBarEmgButton)

public:
	CPvcsToolBarEmgButton();
	virtual ~CPvcsToolBarEmgButton();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void UpdateToolTip(CString pTooltipText);
	void AddToolTip(CString pTooltipText);

protected:
	CToolTipCtrl *m_ToolTip;
	CString m_strTooltipText;

	DECLARE_MESSAGE_MAP()
};


