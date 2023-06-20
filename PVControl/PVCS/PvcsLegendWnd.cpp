// PvcsLegendWnd.cpp : implementation file
//

// Note that it is special implementation for BESI

#include "stdafx.h"
#include "pvcscontrolobjectinfo.h"

#include ".\PvcsControlObjectPowerPack.h"
#include "DxfLayout.h"

#include "PvcsLegendWnd.h"
#include "pvcsconfiguration.h"

#include "PVCSWarningMessage.h"//JSD


// CPvcsLegendWnd

IMPLEMENT_DYNAMIC(CPvcsLegendWnd, CWnd)
CPvcsLegendWnd::CPvcsLegendWnd() {
    m_PrevScrollY = 0;
    SplitScreens = theConfiguration().GetSplitScreens();

    m_hMemDC = CreateCompatibleDC(NULL);
    m_ptrTankMap = NULL;


    if (!m_hMemDC) MessageBox("Cannot create memDC for legend list");
}

CPvcsLegendWnd::~CPvcsLegendWnd() {
}


BEGIN_MESSAGE_MAP(CPvcsLegendWnd, CWnd)
ON_WM_PAINT()
ON_WM_SIZE()
ON_WM_MOUSEMOVE()
ON_WM_VSCROLL()

END_MESSAGE_MAP()

// Function name   : CPvcsLegendWnd::Draw
// Description     : Draws the Legend Info on the Memory buffer
// Return type     : void
// Argument        : void

void CPvcsLegendWnd::Draw(void) {
    using namespace Gdiplus;
    if (CDxfLayout::PwrPack) {
        CDxfLayout::PwrPack->Draw();
    }
    // Load the Legend List
    LoadLegendList();

    map<CString, COLORREF>::const_iterator it = m_mapLegend.begin();


    //Graphics    graphics(m_hMemDC);

    Graphics graphics(m_hMemDC, m_hMemDC_Scaled); // Attach graphics to bitmap buffer
    if (graphics.GetLastStatus() == Ok) {
        // First draw the title "Legend"
        CRect rectWindow;
        GetClientRect(&rectWindow);
        SolidBrush brush(Color::White); 
        rectWindow.right *= LONG(1);
        rectWindow.bottom *= LONG(4);
        FontFamily fontFamily(L"Tahoma");
        Gdiplus::Font font(&fontFamily, 20, FontStyleBold, UnitPixel);
        RectF rectF(0.0f, 0.0f, (float)rectWindow.right, 30.0f);

        graphics.FillRectangle(&brush, rectWindow.left, rectWindow.top, rectWindow.Width(), rectWindow.Height());
        StringFormat stringFormat;
        stringFormat.SetAlignment(StringAlignmentCenter);

        graphics.SetSmoothingMode(SmoothingModeHighQuality);
        graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);

        COLORREF color1 = GetSysColor(COLOR_GRADIENTACTIVECAPTION), color2 = GetSysColor(COLOR_ACTIVECAPTION);

        LinearGradientBrush lgbrBlue(rectF,
                                     Color(GetRValue(color1), GetGValue(color1), GetBValue(color1)),
                                     Color(GetRValue(color2) / 2, GetGValue(color2) / 2, GetBValue(color2) / 2), 90);
        graphics.FillRectangle(&lgbrBlue, rectF);
        if (SplitScreens == 1) {
            if (!CPvcsControlObjectPowerPack::AlarmSet.empty()) {
                brush.SetColor(Color(255, 0, 0));
                graphics.DrawString(L"Powerpack Alarm", -1, &font, rectF, &stringFormat, &brush);
            }else if (!CPvcsControlObjectPowerPack::WarningSet.empty()) {
                brush.SetColor(Color(255, 255, 0));
                graphics.DrawString(L"Powerpack Warning", -1, &font, rectF, &stringFormat, &brush);
            }else{
                brush.SetColor(Color(0, 255, 0));
                graphics.DrawString(L"Powerpack OK", -1, &font, rectF, &stringFormat, &brush);
            }
        } else {
            graphics.DrawString(L"Legend", -1, &font, rectF, &stringFormat, &brush);
        }

        // Now draw the list
        brush.SetColor(Color::Beige);
        graphics.FillRectangle(&brush, 0.0f, 31.0f, 30.0f, static_cast<float>(rectWindow.bottom));

        float curypos = 32.0f;
        Gdiplus::Font labfont(&fontFamily, 12, FontStyleRegular, UnitPixel);

        while (it != m_mapLegend.end()) {
            brush.SetColor(Color::Black);
            COLORREF colorLegend = (*it).second;

            // Draw the legend info text
            PointF pt(35.0f, curypos + 6.0f);
            BSTR str = (*it).first.AllocSysString();
            graphics.DrawString(str, -1, &labfont, pt, &brush);
            SysFreeString(str);

            // path conatins the color Box
            GraphicsPath path;
            path.AddLine(3.0f, curypos + 7.0f, 3.0f, curypos + 17.0f);
            path.AddArc(3.0f, curypos + 14.0f, 6.0f, 6.0f, 90.0f, 90.0f);
            path.AddLine(6.0f, curypos + 20.0f, 24.0f, curypos + 20.0f);
            path.AddArc(21.0f, curypos + 14.0f, 6.0f, 6.0f, 0.0f, 90.0f);
            path.AddLine(27.0f, curypos + 17.0f, 27.0f, curypos + 7.0f);
            path.AddArc(21.0f, curypos + 4.0f, 6.0f, 6.0f, -90.0f, 90.0f);
            path.AddLine(24.0f, curypos + 4.0f, 6.0f, curypos + 4.0f);
            path.AddArc(3.0f, curypos + 4.0f, 6.0f, 6.0f, -180.0f, 90.0f);

            // Draw the color box
            Pen pen(Color(255, GetRValue(colorLegend) / 2, GetGValue(colorLegend) / 2, GetBValue(colorLegend) / 2));
            brush.SetColor(Color(255, GetRValue(colorLegend), GetGValue(colorLegend), GetBValue(colorLegend)));
            graphics.FillPath(&brush, &path);
            graphics.DrawPath(&pen, &path);

            pen.SetColor(Color::SlateGray);
            curypos += 25.0f;
            graphics.DrawLine(&pen, 0.0f, curypos, static_cast<float>(rectWindow.right), curypos);

            ++it;
        } // while( it != m_mapLegend.end() )

    } // if( graphics.GetLastStatus() == Ok )
}


// Function name   : CPvcsLegendWnd::OnPaint
// Description     : Message handler for WM_PAINT
// Return type     : void

void CPvcsLegendWnd::OnPaint() {
    CPaintDC dc(this); // device context for painting
    CRect rc;
    GetClientRect(&rc);

    // First draw the legend to the buffer
    Draw();

    // Now copy the buffer to the window
    double xCurScrollPos = GetScrollPos(SB_HORZ);
    double yCurScrollPos = GetScrollPos(SB_VERT);
    double ScrollWidth = rc.Width();
    double ScrollHeight = 6 * rc.Height();
    double xCurPos = 0.0;
    double yCurPos = 0.0;
    xCurPos = max(0.0, xCurScrollPos * ScrollWidth / double(GetScrollLimit(SB_HORZ) - 1));
    yCurPos = max(0.0, yCurScrollPos * ScrollHeight / double(GetScrollLimit(SB_VERT) - 1));

    // The drawing has already being done on memory buffer pointed by m_hMemDC
    // so just copy the drawn Bitmap to the window
    BitBlt(dc, 0, 0, rc.Width(), rc.Height(), m_hMemDC, int(xCurPos), int(yCurPos), SRCCOPY);
    CWnd::OnPaint();
}


// Function name   : CPvcsLegendWnd::LoadLegendList
// Description     : Loads the legend list
// Return type     : void
// Argument        : void
void CPvcsLegendWnd::LoadLegendList(void) {
    pair<CString, COLORREF> pairLegend;

    m_mapLegend.clear();

    if (SplitScreens != 1) {
        CPvcsTankData tankData;

        /*while( theShipData().m_bIsBusy );
     theShipData().m_bIsBusy = true;*/ //  , now no need, having different copy.

        //CPvcsShipData::TankMap_it it = theShipData().GetTankMap().begin();,   old

        if (m_ptrTankMap == NULL) m_ptrTankMap = theShipData().m_DefaultTankMap;

        CPvcsShipData::TankMap_it it = m_ptrTankMap->begin();

        //while( it != theShipData().GetTankMap().end() ),  old
        while (it != m_ptrTankMap->end()) {
            pairLegend.first = (*it).second.GetCargoType();

            CString strtemp = (*it).second.GetCargoColor();

            if (strtemp != "") sscanf_s(strtemp, "%x", &pairLegend.second);
            else pairLegend.second = RGB(255, 255, 255);

            if (pairLegend.first.GetLength()) m_mapLegend.insert(pairLegend);

            ++it;
        } // while( it != theShipData().GetTankMap().end() )

        /*theShipData().m_bIsBusy = false;*/
    }
}


// Function name   : CPvcsLegendWnd::OnSize
// Description     : Message Handler for WM_SIZE
// Return type     : void
// Argument        : UINT nType
// Argument        : int cx
// Argument        : int cy

void CPvcsLegendWnd::OnSize(UINT nType, int cx, int cy) {
    CWnd::OnSize(nType, cx, cy);

    if (cx || cy) {
        CClientDC dc(this);
        CRect rect;
        GetClientRect(&rect);
        int DlgCtrlID = GetDlgCtrlID();
        if (DlgCtrlID) {
            rect.right *= LONG(1);
            rect.bottom *= LONG(4);
        }

        //SelectObject( m_hMemDC,  CreateCompatibleBitmap( dc, rect.Width(), rect.Height() ) );

        m_hMemDC_Scaled = SelectObject(m_hMemDC, CreateCompatibleBitmap(dc, rect.Width(), rect.Height())); //EHSMark
        RedrawWindow();
    } // if( cx || cy )

}

void CPvcsLegendWnd::OnMouseMove(UINT nFlags, CPoint point) {
    // If mouse is here, close the Control Window
    if (theController().m_hWnd) {
        //theController().DestroyWindow();
        if (PVCSWarningMessage::DialgVisible == false) ::SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);
    }

    CWnd::OnMouseMove(nFlags, point);
}

void CPvcsLegendWnd::SetTankMap(CPvcsShipData::TankMap *pTankMap) {
    m_ptrTankMap = pTankMap;

    if (m_ptrTankMap == NULL) m_ptrTankMap = theShipData().m_DefaultTankMap;
}

void CPvcsLegendWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
    // its horizontal scroll bar
    int nCurPos = GetScrollPos(SB_VERT);
    bool EndScroll = false;
    // decide what to do for each diffrent scroll event
    switch (nSBCode) {
    case SB_LEFT:
        nCurPos = 0;
        break;
    case SB_RIGHT:
        nCurPos = GetScrollLimit(SB_VERT) - 1;
        break;
    case SB_LINELEFT:
        if (nCurPos > 0) nCurPos--;
        break;
    case SB_LINERIGHT:
        if (nCurPos < GetScrollLimit(SB_VERT) - 1) nCurPos++;
        break;
    case SB_PAGELEFT:
        nCurPos = 0;
        break;
    case SB_PAGERIGHT:
        nCurPos = GetScrollLimit(SB_VERT) - 1;
        break;
    case SB_THUMBTRACK:
    case SB_THUMBPOSITION:
        nCurPos = nPos;
        break;
    case SB_ENDSCROLL:
        EndScroll = true;
        break;
    }
    if (!EndScroll) {
        m_PrevScrollY = SetScrollPos(SB_VERT, nCurPos);
        CRect rect;
        GetClientRect(&rect);
        double ScrollHeight = rect.Height();
        int yScroll = int((m_PrevScrollY - nCurPos) * ScrollHeight / double(GetScrollLimit(SB_VERT)));
        ScrollWindow(0, yScroll);
    }
    CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

