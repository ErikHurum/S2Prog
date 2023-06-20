// PvcsToolBarAlarmButton.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsToolBarPumpButton.h"
//#include ".\pvcswagocontrol.h"
//#include ".\pvcsshipdata.h"

#define ID_PUMP_BUTTON_TIMER 12346

// CPvcsToolBarPumpButton


set<CPvcsToolBarPumpButton *>CPvcsToolBarPumpButton::MySet;
IMPLEMENT_DYNAMIC(CPvcsToolBarPumpButton, CButton)
CPvcsToolBarPumpButton::CPvcsToolBarPumpButton() {
	ObjectInit();
}

CPvcsToolBarPumpButton::CPvcsToolBarPumpButton(CString Caption, CRect prect) {
	ObjectInit();
	m_strCaption        = Caption;
	m_rect              = prect;
}

void CPvcsToolBarPumpButton::ObjectInit(void) {
	MySet.insert(this);
	text_colour			= GetSysColor(COLOR_BTNTEXT);
	background_colour	= GetSysColor(COLOR_BTNFACE);
	m_PreviousColor     = background_colour;
	m_ToolTip = new CToolTipCtrl();
	m_ToolTip->Create(this, TTS_ALWAYSTIP);
	m_ToolTip->AddTool(this, "Button");
	m_ToolTip->UpdateTipText("Ready", this);
	m_ToolTip->Activate(true);
	m_InfoButtonIndex 			= 0;
	m_InitCompleted   			= false;
	m_bInRemoteControl     		= false;
	m_bInReleaseControlReq 		= false;
	m_bInReleaseControlReqSignal= false;
	b_InHasControl      		= false;
	b_InControlReq      		= false;
	b_OutControlRequest 		= false;
	b_OutControlRelease 		= false;
	b_OutControlAbort   		= false;

	m_InReleaseControlReqHighCnt= 0;
	m_InReleaseControlReqLowCnt = 0;
}

CPvcsToolBarPumpButton::~CPvcsToolBarPumpButton() {
	delete m_ToolTip;
}


BEGIN_MESSAGE_MAP(CPvcsToolBarPumpButton, CButton)
ON_WM_CREATE()
ON_WM_TIMER()
END_MESSAGE_MAP()

int CPvcsToolBarPumpButton::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	//lpCreateStruct->dwExStyle |= BS_OWNERDRAW;

	if (CButton::OnCreate(lpCreateStruct) == -1) return -1;

	SetTimer(ID_PUMP_BUTTON_TIMER, 1000, NULL);

	return 0;
}

void CPvcsToolBarPumpButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
	// This code only works with buttons.
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);
	UINT uStyle = DFCS_BUTTONPUSH;
	// If drawing selected, add the pushed style to DrawFrameControl.
	if (lpDrawItemStruct->itemState & ODS_SELECTED) uStyle |= DFCS_PUSHED;

	// Draw the button frame.
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem,
					   DFC_BUTTON, uStyle);
	{
		CDC myDC;
		CRect	TextRect(lpDrawItemStruct->rcItem.left + 2, lpDrawItemStruct->rcItem.top + 2, lpDrawItemStruct->rcItem.right - 2, lpDrawItemStruct->rcItem.bottom - 2);
		myDC.Attach(lpDrawItemStruct->hDC);
		DrawFilledRect(&myDC, TextRect, background_colour);
		DrawButtonText(&myDC, TextRect, m_strCaption, text_colour);
	}
}


void CPvcsToolBarPumpButton::DrawFilledRect(CDC *dc, CRect r, COLORREF colour) {
	CBrush B;

	B.CreateSolidBrush(colour);
	dc->FillRect(r, &B);
}

void CPvcsToolBarPumpButton::DrawButtonText(CDC *dc, CRect r, const char *Buf, COLORREF text_colour) {
	COLORREF previous_colour;

	previous_colour = dc->SetTextColor(text_colour);
	dc->SetBkMode(TRANSPARENT);
	dc->DrawText(Buf, strlen(Buf), r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc->SetTextColor(previous_colour);
}
#pragma warning (disable: 4101)

void CPvcsToolBarPumpButton::SetColor(COLORREF pTextColor, COLORREF pBackColor, CString pText) {
	try {
		text_colour 		= pTextColor;
		background_colour 	= pBackColor;
		m_strCaption		= pText;
		Invalidate();
	} catch (exception &e) {}

}

void CPvcsToolBarPumpButton::OnTimer(UINT nIDEvent) {
	if (!m_InitCompleted) {
		m_InitCompleted = true;
		m_ButtonInfoPtr = CPumpButtonOperation::m_PumpButtonInfo[m_InfoButtonIndex];
		if (m_ButtonInfoPtr) {
			b_InHasControl      = CPumpButtonOperation::FindObject(m_ButtonInfoPtr->FunctionMap, INP_FUNC_IN_HAS_CONTROL, m_InHasControl);
			b_InControlReq      = CPumpButtonOperation::FindObject(m_ButtonInfoPtr->FunctionMap, INP_FUNC_IN_CONTROL_REQUEST, m_InControlReq);
			b_OutControlRequest = CPumpButtonOperation::FindObject(m_ButtonInfoPtr->FunctionMap, INP_FUNC_OUT_REQUEST_CONTROL, m_OutControlRequest);
			b_OutControlRelease = CPumpButtonOperation::FindObject(m_ButtonInfoPtr->FunctionMap, INP_FUNC_OUT_RELEASE_CONTROL, m_OutControlRelease);
			b_OutControlAbort   = CPumpButtonOperation::FindObject(m_ButtonInfoPtr->FunctionMap, INP_FUNC_OUT_ABORT_REQUEST, m_OutControlAbort);
		}
	} else {
		if (m_ButtonInfoPtr) {
			static clock_t mTimeBlink = clock();
			static clock_t mTimeSec   = clock();
			static int mBlinkDelay    = 750;
			static bool mBlink = false;

			clock_t 	   CurrentTime   = clock();

			if (CurrentTime >= mTimeBlink + mBlinkDelay) {
				if (mBlinkDelay == 750) {
					mBlink      = false;
					mBlinkDelay = 250;
				} else {
					mBlink      = true;
					mBlinkDelay = 750;
				}
				mTimeBlink = CurrentTime;
			}
			if (CurrentTime >= mTimeSec + 1000) {
				mTimeSec = CurrentTime;
			}

			if (m_bInRemoteControl) {
				if (m_bInReleaseControlReq) {
					if (mBlink) {
						SetColor(RGB(0, 0, 0), RGB(255, 255, 0), "Release Request");
					} else {
						SetColor(RGB(255, 255, 255), RGB(0, 0, 0), "Release Request");
					}

				} else {
					SetColor(RGB(255, 255, 255), RGB(0, 147, 0), "PVCS control");
				}
			} else {
				SetColor(RGB(0, 0, 0), RGB(255, 255, 0), "Remote");
			}
		}
	}
	CButton::OnTimer(nIDEvent);
}


void CPvcsToolBarPumpButton::AddToolTip(CString pTooltipText) {
	if (!pTooltipText.IsEmpty()) {
		m_ToolTip->Activate(FALSE);
		m_ToolTip->AddTool(this, "Button");
	}
	return;
}

void CPvcsToolBarPumpButton::UpdateToolTip(CString pTooltipText) {
	if (!pTooltipText.IsEmpty()) {
		m_ToolTip->UpdateTipText(pTooltipText, this);
		m_ToolTip->Activate(true);
	} else if (::IsWindow(m_ToolTip->m_hWnd)) m_ToolTip->Activate(false);

}


void CPvcsToolBarPumpButton::SetPointerToButtonInfo(int pInfoButtonIndex) {
	m_InfoButtonIndex = pInfoButtonIndex;
}


int CPvcsToolBarPumpButton::GetPointerToButtonInfo(void) {
	return m_InfoButtonIndex;
}

bool CPvcsToolBarPumpButton::SetReleaseControl(bool p_bOutControlRelease) {
	bool mStatus1 = false;
	// To be moved to the thread
	if (b_OutControlRelease) {
		mStatus1 = CPvcsWagoControl::theWagoUnit().SetValue(m_OutControlRelease, (const bool)p_bOutControlRelease);
	}
	return mStatus1;
}

bool CPvcsToolBarPumpButton::SetAbortControlRequest(bool p_bOutAbortControlRelease) {
	bool mStatus1 = false;
	// To be moved to the thread
	if (b_OutControlRelease) {
		mStatus1 = CPvcsWagoControl::theWagoUnit().SetValue(m_OutControlAbort, (const bool)p_bOutAbortControlRelease);
	}
	return mStatus1;
}


bool CPvcsToolBarPumpButton::SetControlRequest(bool p_bOutControlRequest) {
	bool mStatus1 = false;
	// To be moved to the thread
	if (b_OutControlRelease) {
		mStatus1 = CPvcsWagoControl::theWagoUnit().SetValue(m_OutControlRequest, (const bool)p_bOutControlRequest);
	}
	return mStatus1;
}


bool CPvcsToolBarPumpButton::HasControl(void) {
	return m_bInRemoteControl;
}

bool CPvcsToolBarPumpButton::HasReceivedControlRequest(void) {
	return m_bInRemoteControl && m_bInReleaseControlReq;
}

void CPvcsToolBarPumpButton::ResetHasReceivedControlRequest(void) {
	m_bInReleaseControlReq = false;
}


bool CPvcsToolBarPumpButton::ButtonConfigOK(void) {
	return b_InControlReq && b_InHasControl && b_OutControlAbort && b_OutControlRelease && b_OutControlRequest;
}


CString CPvcsToolBarPumpButton::GetMessage(void) {
	return m_strCaption;
}


bool CPvcsToolBarPumpButton::CheckInReleaseControlReq(void)
{
	// Check if we have any reason to read request signal
	bool StatusOK = CPvcsWagoControl::theWagoUnit().GetPumpButtonInput(m_InHasControl, m_bInRemoteControl);
	if (StatusOK && m_bInRemoteControl) {
		bool bPrevInReleaseControlReqSignal = m_bInReleaseControlReqSignal;

		StatusOK = CPvcsWagoControl::theWagoUnit().GetPumpButtonInput(m_InControlReq, m_bInReleaseControlReqSignal);
		if ( StatusOK && m_bInRemoteControl ){
			if (  m_bInReleaseControlReqSignal && !bPrevInReleaseControlReqSignal ) {
				m_InReleaseControlReqHighCnt++;
			}else if (  !m_bInReleaseControlReqSignal && bPrevInReleaseControlReqSignal && m_InReleaseControlReqHighCnt ){
				m_InReleaseControlReqLowCnt++;
			}
			// We have a high - low pulse
			if (m_InReleaseControlReqHighCnt && m_InReleaseControlReqLowCnt) {
				m_bInReleaseControlReq		 = true;
				m_InReleaseControlReqHighCnt = 0;
				m_InReleaseControlReqLowCnt  = 0;
			}
		} else {
			m_bInReleaseControlReqSignal = false;
			m_InReleaseControlReqHighCnt = 0;
			m_InReleaseControlReqLowCnt  = 0;
		}
	}
	return m_bInReleaseControlReqSignal;
}


