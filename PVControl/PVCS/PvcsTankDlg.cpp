// PvcsTankDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsTankDlg.h"
#include "PVCSAlarmCtrl.h"//Added JSD
#include "pvcssplitterwnd.h"
#include "PVCSWarningMessage.h"//JSD
#include "tankdata.h"
int CPvcsTankDlg::AlmCtrlDlgClicked;
int CPvcsTankDlg::m_iGreenAcknow = 0;

// CPvcsTankDlg dialog

CPvcsShipData::TankMap *CPvcsTankDlg::m_ptrTankMap = NULL;

IMPLEMENT_DYNAMIC(CPvcsTankDlg, CDialog)
CPvcsTankDlg::CPvcsTankDlg(CWnd *pParent /*=NULL*/)
    : CDialog(CPvcsTankDlg::IDD, pParent)
    , m_iTankID(10)
    , m_strFile(_T(""))
    , m_bActive(false)
    , m_bMustUpdate(false)
    , m_bChangePos(true)
    , m_bFlash(false)
    , m_bFlashState(false)
    , m_bAlarmActive(false)
    , m_bAlarmAcknowledged(false) {
    m_hTheme = OpenThemeData(m_hWnd, L"WINDOW");
    SplitScreens = theConfiguration().GetSplitScreens();
}

CPvcsTankDlg::~CPvcsTankDlg() {

}

void CPvcsTankDlg::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPvcsTankDlg, CDialog)
ON_WM_CREATE()
ON_WM_PAINT()
ON_WM_CLOSE()
ON_WM_SHOWWINDOW()
ON_WM_LBUTTONDOWN()
ON_WM_NCLBUTTONDOWN()
ON_WM_NCPAINT()
ON_WM_TIMER()
ON_WM_MOUSEMOVE()
ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()


// CPvcsTankDlg message handlers

int CPvcsTankDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CDialog::OnCreate(lpCreateStruct) == -1) return -1;

    CRect rectParent;


    GetParent()->GetClientRect(&rectParent);
    if (SplitScreens == 2) {
        rectParent.right /= 2;
        MoveWindow(&rectParent);


        CRect rectWindowLayout, rectWindowList;
        const int iListWidth = 150;

        GetClientRect(&rectWindowLayout);
        rectWindowList = rectWindowLayout;
        rectWindowList.left = rectWindowLayout.right - iListWidth;
        rectWindowLayout.right -= (iListWidth + 2);
        rectWindowLayout.top += 30;

        m_dxfLayout.Create(rectWindowLayout, this);
        m_tankValueList.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rectWindowList, this, IDC_TANKVALUELIST);
        m_tankValueList.SetTankID(m_iTankID);

        m_dxfLayout.Open(m_strFile, m_strTankLayer, false);

        CString str;
        str.Format("Tank Window %d", m_iTankID);
        SetWindowText(str);

    } else {
        MoveWindow(&rectParent);
        CRect rectWindowLayout;

        GetClientRect(&rectWindowLayout);
        rectWindowLayout.top += 30;

        m_dxfLayout.Create(rectWindowLayout, this);

        m_dxfLayout.Open(m_strFile, m_strTankLayer);
        //m_dxfShipLayout.Open(theConfiguration().GetScreenFile(CPVCSApp::ScreenIndex),theConfiguration().GetScreenTankLayer(CPVCSApp::ScreenIndex),theConfiguration().GetScreenColor(CPVCSApp::ScreenIndex),theConfiguration().GetScreenBckGndColor(CPVCSApp::ScreenIndex),true);

        CString str;
        str.Format("Tank Window %d", m_iTankID);
        SetWindowText(str);
    }
    SetTimer(222, 1000, NULL);
    // *********** Done by  , as told by Asle, to remove Red color bar and Alarm text
    //SetTimer( IDT_ALARM_BEEP, 10000, NULL );
    return 0;
}

void CPvcsTankDlg::OnPaint() {
    CPaintDC dc(this); // device context for painting

    using namespace Gdiplus;

    CRect rectWindow;
    GetClientRect(rectWindow);
    if (SplitScreens == 1) {
        rectWindow.right -= 153;
    }

    COLORREF color1 = GetSysColor(COLOR_GRADIENTINACTIVECAPTION), color2 = GetSysColor(COLOR_ACTIVECAPTION);


    Graphics    graphics(m_hWnd);

    if (graphics.GetLastStatus() == Ok) {
        SolidBrush  brushBlack((unsigned)Color::Black);
        SolidBrush  brushGray((unsigned)Color::GhostWhite);
        Pen         pen(Color(GetRValue(color2) / 2, GetGValue(color2) / 2, GetBValue(color2) / 2));
        FontFamily  fontFamily(L"Tahoma");
        Gdiplus::Font        font(&fontFamily, 25, FontStyleBold, UnitPixel);
        float rWidth = rectWindow.Width();
        if (theConfiguration().GetSplitScreens() != 2) {
            rWidth += 120;
        } else {
            rWidth -= 120;
        }
        RectF  rectF(0.0f, 0.0f, rWidth, 27.0f);

        StringFormat stringFormat;
        stringFormat.SetAlignment(StringAlignmentCenter);

        graphics.SetSmoothingMode(SmoothingModeHighQuality);
        graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

        CString strtemp;

        m_bAlarmActive = false;
        m_bAlarmAcknowledged = false;

        GetWindowText(strtemp);
        BSTR str = strtemp.AllocSysString();
        LinearGradientBrush lgbrOrange(rectF, (unsigned)Color::LightYellow, (unsigned)Color::Orange, 90);
        LinearGradientBrush lgbrTitle(rectF,
                                      Color(GetRValue(color1), GetGValue(color1), GetBValue(color1)),
                                      Color(GetRValue(color2), GetGValue(color2), GetBValue(color2)), 90);
        graphics.DrawRectangle(&pen, rectF);
        if (m_bActive) {
            graphics.FillRectangle(&lgbrOrange, rectF);
            graphics.DrawString(str, -1, &font, rectF, &stringFormat, &brushBlack);
        } else {
            graphics.FillRectangle(&lgbrTitle, rectF);
            graphics.DrawString(str, -1, &font, rectF, &stringFormat, &brushBlack);
        }
        SysFreeString(str);
    } // if( graphics.GetLastStatus() == Ok )

}

BOOL CPvcsTankDlg::Create(const CString& param_strFile, const CString& param_strTankLayer, const int& param_ScaleX, const int& param_ScaleY, const int& param_BackGroundCol, const int& param_UndefObjectCol, const int& param_ObjectCol, const int param_LineCol, const int param_TextCol, const bool param_hasLineCol, const bool param_hasTextCol, const bool param_hasBackGround, const int& param_iTankID, CWnd* param_pParent){
    m_strFile       = param_strFile;
    m_strTankLayer  = param_strTankLayer;
    m_iTankID       = param_iTankID;

    m_dxfLayout.SetScale(param_ScaleX, param_ScaleY, param_BackGroundCol, param_UndefObjectCol, param_ObjectCol,  param_LineCol,  param_TextCol, param_hasLineCol,  param_hasTextCol, param_hasBackGround);

    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = this->m_hWnd;

    ::_TrackMouseEvent(&tme);

    return CDialog::Create(IDD_PVCSTANKDLG, param_pParent);
}

const int& CPvcsTankDlg::GetTankID(void) {
    return m_iTankID;
}

void CPvcsTankDlg::SetActive(const bool &param_bStatus) {
    m_bActive = param_bStatus;
    // if ( m_bActive /*&& m_bActive != param_bStatus*/ ) {
    RedrawWindow();
    OnNcPaint();
    //}
}

void CPvcsTankDlg::OnClose() {
    m_bMustUpdate = false;
    m_bAlarmActive = false;
    m_bAlarmAcknowledged = false;

    CPvcsSplitterWnd *pMainSplitterWnd =
        dynamic_cast<CPvcsSplitterWnd *>(GetParent()->GetParent());
    // EHSMark
    if (pMainSplitterWnd) {

        pMainSplitterWnd->ActivateTank(NOTANK);
    }

    CDialog::OnClose();
}

bool CPvcsTankDlg::MustUpdate(void) {
    return m_bMustUpdate;
}

void CPvcsTankDlg::OnShowWindow(BOOL bShow, UINT nStatus) {
    CDialog::OnShowWindow(bShow, nStatus);

    m_bMustUpdate = true;
}

void CPvcsTankDlg::SetUpdate(bool param_bMustUpdate) {
    m_bMustUpdate = param_bMustUpdate;

//	m_dxfLayout.EnableDraw( param_bMustUpdate );
}

BOOL CPvcsTankDlg::OnInitDialog() {
    CDialog::OnInitDialog();

    CMenu *pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL) {
        pSysMenu->DeleteMenu(SC_MOVE, MF_BYCOMMAND);
    }
// *********** Done by  , as told by Asle, to remove Red color bar and Alarm text
//SetTimer( IDT_ALARM_FLASH, 500, NULL );

    // Initialize and attach tool tip to the dialog
    m_ToolTip.Create(this, TTS_ALWAYSTIP);
    m_ToolTip.Activate(FALSE);
    m_ToolTip.AddTool(GetDlgItem(IDC_DXFLAYOUT), "Layout");

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPvcsTankDlg::OnLButtonDown(UINT nFlags, CPoint point) {
    // First of all close the Control Window
    if (theController().m_hWnd) {
        //theController().DestroyWindow();
        if (PVCSWarningMessage::DialgVisible == true) {
            theWarningMessage().OnClose();
            //::SendMessage( theController().m_hWnd, WM_CLOSE, 0, 0 );

        }
        ::SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);
    }

    if (PVCSWarningMessage::DialgVisible == false) {
        // Tell the parent splitter window to activate this dialog
        CPvcsSplitterWnd *tempSplitterWnd = dynamic_cast<CPvcsSplitterWnd *>(GetParent()->GetParent());
        m_bChangePos = false;

        if (tempSplitterWnd) tempSplitterWnd->ActivateTank(m_iTankID);
    }

    // Close any alarm beeps
    //Start JSD
    if (CPvcsTankDlg::m_ptrTankMap == NULL) CPvcsTankDlg::m_ptrTankMap = theShipData().m_DefaultTankMap;


    CDialog::OnLButtonDown(nFlags, point);
}

BOOL CPvcsTankDlg::PreCreateWindow(CREATESTRUCT &cs) {
    // TODO: Add your specialized code here and/or call the base class

    return CDialog::PreCreateWindow(cs);
}

void CPvcsTankDlg::OnNcLButtonDown(UINT nHitTest, CPoint point) {
    PostMessage(WM_LBUTTONDOWN);

    CRect wndRect;
    GetWindowRect(&wndRect);
    wndRect.OffsetRect(-wndRect.left, -wndRect.top);

    CRect m_closeRect(wndRect);

    m_closeRect.left = m_closeRect.right - GetSystemMetrics(SM_CXSMSIZE) + 2;
    m_closeRect.bottom = GetSystemMetrics(SM_CYSMSIZE) - 2;

    m_closeRect.OffsetRect(-5, 4);

    ScreenToClient(&point);
    point.x += 3;
    point.y += 21;

    if (point.x >= m_closeRect.left
        && point.y >= m_closeRect.top
        && point.x <= m_closeRect.right
        && point.y <= m_closeRect.bottom) PostMessage(WM_CLOSE);
}

void CPvcsTankDlg::OnNcPaint() {
    // TODO: Add your message handler code here
    // Do not call CDialog::OnNcPaint() for painting messages

    CWindowDC dc(this);

    CRect wndRect;
    GetWindowRect(&wndRect);
    wndRect.OffsetRect(-wndRect.left, -wndRect.top);

    CRect leftRect(wndRect), topRect(wndRect), rightRect(wndRect), bottomRect(wndRect), m_closeRect(wndRect);

    leftRect.right  = GetSystemMetrics(SM_CXEDGE) + 1;
    topRect.bottom  = GetSystemMetrics(SM_CYSMCAPTION) + 3;
    rightRect.left  = rightRect.right - GetSystemMetrics(SM_CXEDGE) - 1;
    bottomRect.top  = bottomRect.bottom - GetSystemMetrics(SM_CXEDGE) - 1;

    rightRect.top = GetSystemMetrics(SM_CYSMCAPTION) + 3;
    leftRect.top = GetSystemMetrics(SM_CYSMCAPTION) + 3;

    m_closeRect.left = m_closeRect.right - GetSystemMetrics(SM_CXSMSIZE) + 2;
    m_closeRect.bottom = GetSystemMetrics(SM_CYSMSIZE) - 2;

    m_closeRect.OffsetRect(-5, 4);

    if (m_hTheme) {
        if (m_bActive) {
            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_SMALLCAPTION,
                CS_ACTIVE,
                topRect,
                NULL);

            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_FRAMELEFT,
                FS_ACTIVE,
                leftRect,
                NULL);

            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_FRAMERIGHT,
                FS_ACTIVE,
                rightRect,
                NULL);

            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_FRAMEBOTTOM,
                FS_ACTIVE,
                bottomRect,
                NULL);

            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_SMALLCLOSEBUTTON,
                CBS_NORMAL,
                m_closeRect,
                NULL);

        } // if( m_bActive )
        else {
            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_SMALLCAPTION,
                CS_INACTIVE,
                topRect,
                NULL);

            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_FRAMELEFT,
                FS_INACTIVE,
                leftRect,
                NULL);

            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_FRAMERIGHT,
                FS_INACTIVE,
                rightRect,
                NULL);

            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_FRAMEBOTTOM,
                FS_INACTIVE,
                bottomRect,
                NULL);

            DrawThemeBackground(
                m_hTheme,
                dc,
                WP_SMALLCLOSEBUTTON,
                CBS_DISABLED,
                m_closeRect,
                NULL);

        }
    }

    using namespace Gdiplus;
    //while( theShipData().m_bIsBusy );//  old
    //theShipData().m_bIsBusy = true; //  old
    if (CPvcsTankDlg::m_ptrTankMap == NULL) CPvcsTankDlg::m_ptrTankMap = theShipData().m_DefaultTankMap;
    //RedrawWindow();
}

void CPvcsTankDlg::ShowToolTip(const CString &param_strToolTip) {
    // Check if tool tip string has text or not
    if (param_strToolTip.GetLength()) {
        static CString OrgStr;
        if (OrgStr != param_strToolTip) {
            OrgStr = param_strToolTip;
            m_ToolTip.UpdateTipText(OrgStr, GetDlgItem(IDC_DXFLAYOUT));
        }
        m_ToolTip.Activate(TRUE); // Show tooltip

    } // if( param_strToolTip.GetLength() )
    else m_ToolTip.Activate(FALSE); // Hide tooltip
}

BOOL CPvcsTankDlg::PreTranslateMessage(MSG *pMsg) {
    // Send message to the tool tip
    m_ToolTip.RelayEvent(pMsg);

    if (pMsg->message == WM_CAPTURECHANGED) {
        //TRACE("Leave\n");
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CPvcsTankDlg::OnTimer(UINT nIDEvent) {
    // *********** Done by  , as told by Asle, to remove Red color bar and Alarm text
    //// Toggle flash state
    //if(m_bAlarmAcknowledged==false&&(m_iGreenAcknow==0))//Jsd22FEB2007
    //{
    //if( m_bFlash && nIDEvent == IDT_ALARM_FLASH )
    //{
    //	m_bFlashState = m_bFlashState == true ? false : true;
    //	RedrawWindow();
    //	//OnNcPaint();
    //} // if( m_bFlash && nIDEvent == IDT_ALARM_FLASH )
    //}
    //if((m_iGreenAcknow==0)&& m_bAlarmAcknowledged==true)
    //{
    //	OnPaint();
    //	//OnNcPaint();
    //	m_iGreenAcknow=1;
    //}
    //CTankData obj;
    //obj.GetAlarmStatus();
    //if( ( nIDEvent == IDT_ALARM_BEEP ) && !m_bAlarmAcknowledged && (CTankData::m_AlarmStatus!="" && CTankData::m_AlarmStatus=="1") )
    //	//MessageBeep( MB_ICONASTERISK );
    //	//Beep(900,200);

    if (theController().m_hWnd && nIDEvent == 222) CloseControlDlg();

    CDialog::OnTimer(nIDEvent);
}

void CPvcsTankDlg::OnMouseMove(UINT nFlags, CPoint point) {
    // TODO: Add your message handler code here and/or call default

    CDialog::OnMouseMove(nFlags, point);
}

bool CPvcsTankDlg::MousePointerOutOfBounds(CPoint point) {
    CRect rect;

    GetWindowRect(&rect);

    return !rect.PtInRect(point);
}

LRESULT CPvcsTankDlg::OnMouseLeave(WPARAM wParam, LPARAM lParam) {
    TRACE("TRACK\n");
    return LRESULT();
}

void CPvcsTankDlg::CloseControlDlg(void) {
}



