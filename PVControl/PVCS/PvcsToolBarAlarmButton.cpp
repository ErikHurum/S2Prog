// PvcsToolBarAlarmButton.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsToolBarAlarmButton.h"
#include ".\pvcswagocontrol.h"
#include ".\pvcsshipdata.h"

#define ID_ALARM_BUTTON_TIMER 12345

// CPvcsToolBarAlarmButton

IMPLEMENT_DYNAMIC(CPvcsToolBarAlarmButton, CButton)
CPvcsToolBarAlarmButton::CPvcsToolBarAlarmButton() {
}

CPvcsToolBarAlarmButton::CPvcsToolBarAlarmButton(CString Caption, CRect prect) {
    text_colour			= GetSysColor(COLOR_BTNTEXT);
    background_colour	= GetSysColor(COLOR_BTNFACE);
    m_strCaption        = Caption;
    m_rect              = prect;
    m_PreviousColor     = background_colour;
    m_ToolTip = new CToolTipCtrl();
    m_ToolTip->Create(this, TTS_ALWAYSTIP);
    m_ToolTip->AddTool(this, "Button");
    m_ToolTip->UpdateTipText("No Alarm", this);
    m_ToolTip->Activate(true);
}

CPvcsToolBarAlarmButton::~CPvcsToolBarAlarmButton() {
    delete m_ToolTip;
}


BEGIN_MESSAGE_MAP(CPvcsToolBarAlarmButton, CButton)
ON_WM_CREATE()
ON_WM_TIMER()
END_MESSAGE_MAP()

int CPvcsToolBarAlarmButton::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    lpCreateStruct->dwExStyle |= BS_OWNERDRAW;

    if (CButton::OnCreate(lpCreateStruct) == -1) return -1;

    SetTimer(ID_ALARM_BUTTON_TIMER, 1000, NULL);

    return 0;
}

void CPvcsToolBarAlarmButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
    CDC		*dc;
    CRect	button_rect, text_rect, offset_text_rect;
    UINT	state;

    lpDrawItemStruct->rcItem.bottom = m_rect.bottom;
    lpDrawItemStruct->rcItem.top = m_rect.top;
    lpDrawItemStruct->rcItem.left = m_rect.left;
    lpDrawItemStruct->rcItem.right = m_rect.right;

    dc    = CDC::FromHandle(lpDrawItemStruct->hDC);
    state = lpDrawItemStruct->itemState;

    button_rect.CopyRect(&lpDrawItemStruct->rcItem);

    text_rect = button_rect;
    text_rect.OffsetRect(-1, -1);
    offset_text_rect = text_rect;
    offset_text_rect.OffsetRect(1, 1);

    DrawFilledRect(dc, button_rect, background_colour);
    DrawButtonText(dc, text_rect, m_strCaption, text_colour);
}


void CPvcsToolBarAlarmButton::DrawFilledRect(CDC *dc, CRect r, COLORREF colour) {
    CBrush B;

    B.CreateSolidBrush(colour);
    dc->FillRect(r, &B);
}

void CPvcsToolBarAlarmButton::DrawButtonText(CDC *dc, CRect r, const char *Buf, COLORREF text_colour) {
    COLORREF previous_colour;

    previous_colour = dc->SetTextColor(text_colour);
    dc->SetBkMode(TRANSPARENT);
    dc->DrawText(Buf, strlen(Buf), r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    dc->SetTextColor(previous_colour);
}
#pragma warning (disable: 4101)

void CPvcsToolBarAlarmButton::SetColor(COLORREF pTextColor, COLORREF pBackColor, CString pText) {
    try {
        text_colour			=	pTextColor;
        background_colour	=	pBackColor;
        m_strCaption		=	pText;
        Invalidate(FALSE);
    } catch (exception &e) {}

}


void CPvcsToolBarAlarmButton::OnTimer(UINT nIDEvent) {
    static bool bAlarmBlink = false;

	theShipData().Aquire();

    UINT uiActAlarmSize = theShipData().m_AlarmData.size();
    UINT uiAckAlarmSize = theShipData().m_AckAlarmData.size();

    if (uiActAlarmSize <= 0 && uiAckAlarmSize <= 0) { //No Alarm
        COLORREF CurrentColor = RGB(0, 147, 0);
        if (m_PreviousColor!=CurrentColor ) {
            m_PreviousColor = CurrentColor;
            SetColor(RGB(255, 255, 255), RGB(0, 147, 0), "No Alarm");
        }
    } else if (uiActAlarmSize <= 0 && uiAckAlarmSize > 0) { //Steady Red
        CString strAlarm = "";
        strAlarm.Format("%s - %s", theShipData().m_AckAlarmData[0].TankNameDisplay, theShipData().m_AckAlarmData[0].AlarmText);

        if (strAlarm.GetLength() > 17) strAlarm = strAlarm.Left(17);
        strAlarm += " ...";

        m_PreviousColor = RGB(255, 0, 0);
        SetColor(RGB(255, 255, 255), RGB(255, 0, 0), strAlarm);
    } else if ((uiActAlarmSize > 0 && uiAckAlarmSize <= 0) || (uiActAlarmSize > 0 && uiAckAlarmSize > 0)) { //Active Red
        CString strAlarm = "";
        strAlarm.Format("%s - %s", theShipData().m_AlarmData[0].TankNameDisplay, theShipData().m_AlarmData[0].AlarmText);

        if (strAlarm.GetLength() > 17) strAlarm = strAlarm.Left(17);
        strAlarm += " ...";

        if (bAlarmBlink) {
            m_PreviousColor = RGB(255, 0, 0);
            SetColor(RGB(255, 255, 255), RGB(255, 0, 0), strAlarm);
            bAlarmBlink = false;
        } else {
            m_PreviousColor = RGB(255, 0, 0);
            SetColor(RGB(255, 255, 255), RGB(0, 0, 0), strAlarm);
            bAlarmBlink = true;
        }
    }
    theShipData().Release();
    CButton::OnTimer(nIDEvent);
}
