#pragma once


// CPvcsToolBarAlarmButton

class CPvcsToolBarAlarmButton : public CButton
{
	DECLARE_DYNAMIC(CPvcsToolBarAlarmButton)
private:
	CRect m_rect;
	CString m_strCaption;
	COLORREF text_colour, background_colour, disabled_background_colour;
	COLORREF light, highlight, shadow, dark_shadow;
	CToolTipCtrl *m_ToolTip;
    COLORREF m_PreviousColor;

public:
	CPvcsToolBarAlarmButton();
	CPvcsToolBarAlarmButton(CString caption, CRect prect);
	virtual ~CPvcsToolBarAlarmButton();

	void SetColor(COLORREF pTextColor,COLORREF pBackColor, CString pText);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawButtonText(CDC *dc, CRect r, const char *buf, COLORREF text_colour);
	void DrawFilledRect(CDC *dc, CRect r, COLORREF colour);


protected:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


