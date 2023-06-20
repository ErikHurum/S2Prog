#pragma once

#include ".\PumpButtonOperation.h"
// CPvcsToolBarPumpButton

class CPvcsToolBarPumpButton : public CButton
{
	DECLARE_DYNAMIC(CPvcsToolBarPumpButton)
private:
	CDC myDC;
	CRect m_rect;
	CString m_strCaption;
	COLORREF text_colour, background_colour, disabled_background_colour;
	COLORREF light, highlight, shadow, dark_shadow;
	CToolTipCtrl *m_ToolTip;
    COLORREF m_PreviousColor;
	int m_InfoButtonIndex;
	time_t m_Time;
	bool b_InHasControl     ;
	bool b_InControlReq     ;
	bool b_OutControlRequest;
	bool b_OutControlRelease;
	bool b_OutControlAbort  ;
	DigitalSignal m_InHasControl		;
	DigitalSignal m_InControlReq		;
	DigitalSignal m_OutControlRequest	;
	DigitalSignal m_OutControlRelease	;
	DigitalSignal m_OutControlAbort		;
	bool m_bInRemoteControl    ;
	bool m_bInReleaseControlReq;
	bool m_bInReleaseControlReqSignal;
	unsigned m_InReleaseControlReqHighCnt;
	unsigned m_InReleaseControlReqLowCnt;
	CPumpButtonOperation::ButtonInfo *m_ButtonInfoPtr;
	bool m_InitCompleted;
	void ObjectInit(void);


public:


	static set<CPvcsToolBarPumpButton*>MySet;
	CPvcsToolBarPumpButton();
	CPvcsToolBarPumpButton(CString caption, CRect prect);
	virtual ~CPvcsToolBarPumpButton();

	void SetColor(COLORREF pTextColor,COLORREF pBackColor, CString pText);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawButtonText(CDC *dc, CRect r, const char *buf, COLORREF text_colour);
	void DrawFilledRect(CDC *dc, CRect r, COLORREF colour);

	void UpdateToolTip(CString pTooltipText);
	void AddToolTip(CString pTooltipText);
	void SetPointerToButtonInfo(int pInfoButtonIndex);
	int GetPointerToButtonInfo(void);
	bool SetReleaseControl(bool p_bOutControlRelease);
	bool SetAbortControlRequest(bool p_bOutAbortControlRelease);
	bool SetControlRequest(bool p_bOutControlRequest);
	bool HasControl(void);
	bool HasReceivedControlRequest(void);
	void ResetHasReceivedControlRequest(void);
	CString GetMessage(void);
	bool CheckInReleaseControlReq(void);
	bool ButtonConfigOK(void);

protected:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


