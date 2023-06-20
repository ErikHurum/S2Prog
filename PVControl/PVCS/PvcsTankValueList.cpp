// PvcsTankValueList.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsTankValueList.h"
#include "ipscommunication.h"
#include ".\pvcstankvaluelist.h"

#include "pvcstankdata.h"

const float CPvcsTankValueList::iTitleWidth = 80.0;
const float CPvcsTankValueList::fHeadingHeight = 27.0;

// CPvcsTankValueList

IMPLEMENT_DYNAMIC(CPvcsTankValueList, CWnd)
CPvcsTankValueList::CPvcsTankValueList()
: m_iTankID( 0 )
{
	m_hMemDC = CreateCompatibleDC( NULL );
	m_ptrTankMap = NULL;
	if( !m_hMemDC )
		MessageBox( "Cannot create memDC for tank list" );
}

CPvcsTankValueList::~CPvcsTankValueList()
{
}


BEGIN_MESSAGE_MAP(CPvcsTankValueList, CWnd)
    ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CPvcsTankValueList message handlers

int CPvcsTankValueList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    DrawHeading();
    return 0;

}


void CPvcsTankValueList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect (&rc);

	BitBlt(dc, 0, 0, rc.Width(), rc.Height(), m_hMemDC, 0, 0, SRCCOPY);
}

void CPvcsTankValueList::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if( cx || cy )
	{
		CClientDC dc( this );
		CRect rect;
		GetClientRect( &rect );

		SelectObject( m_hMemDC,  CreateCompatibleBitmap( dc, rect.Width(), rect.Height() ) );

		if(m_ptrTankMap == NULL)
			m_ptrTankMap = theShipData().m_DefaultTankMap;

		Draw(m_ptrTankMap);
	}
}

void CPvcsTankValueList::Draw(CPvcsShipData::TankMap *pTankMap)
{
	using namespace Gdiplus;

   const int iValCount = 10;
	const BSTR strTitle[] = {
		L"Ullage",
		L"Level",
		L"Volume",
		L"Volume %",
		L"Weight",
        L"Temperature",
		L"Tank Pressure",
		L"Line Pressure",
        L"Cargo Type",
		L"Load Rate", 
	};
	CPvcsTankData tankData;

	m_ptrTankMap = pTankMap;
	if(m_ptrTankMap == NULL)
			m_ptrTankMap = theShipData().m_DefaultTankMap;

	//while( theShipData().m_bIsBusy );//  old
	//theShipData().m_bIsBusy = true; //  old
	CString strValue[] = {
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetUllage(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetLevel(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetVolume(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetVolumePercent(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetWeight(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetTemperature(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetTankPressure(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetLinePressure(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetCargoType(),
		theShipData().GetTank( m_iTankID,m_ptrTankMap ).GetLoadRate() };
	//theShipData().m_bIsBusy = false;//  old
	CRect rectWindow;
	GetClientRect( &rectWindow );

	const float fCellHeight = (float)( rectWindow.Height() - fHeadingHeight ) / (float)( iValCount );

	Graphics graphics( m_hMemDC );

	if( graphics.GetLastStatus() == Ok )
	{
        CRect rectWindow;
        GetClientRect( &rectWindow );
		SolidBrush brush( (unsigned)Color::Beige );
		graphics.FillRectangle( &brush, rectWindow.left, LONG(rectWindow.top+fHeadingHeight), rectWindow.right, LONG(rectWindow.bottom-fHeadingHeight ));

		FontFamily  fontFamily(L"Tahoma");
		//Gdiplus::Font        fontHeading(&fontFamily, 20, FontStyleBold, UnitPixel);
		Gdiplus::Font        fontTitle(&fontFamily, 11, FontStyleBold, UnitPixel);
		Gdiplus::Font		fontValue(&fontFamily, 11, FontStyleRegular, UnitPixel);

		RectF		rectFTitle(0.0f, fHeadingHeight, iTitleWidth, fCellHeight);
		RectF		rectFValue(iTitleWidth, fHeadingHeight, (float)rectWindow.right, fCellHeight);

		//RectF		rectFHeading(0.0f, 0.0f, (float)rectWindow.right, fHeadingHeight);

		//COLORREF color1 = GetSysColor( COLOR_GRADIENTACTIVECAPTION );
		COLORREF color2 = GetSysColor( COLOR_ACTIVECAPTION );
/*
		LinearGradientBrush lgbrHeading(rectFHeading,
			Color( GetRValue( color1 ), GetGValue( color1 ), GetBValue( color1 ) ),
			Color( GetRValue( color2 )/2, GetGValue( color2 )/2, GetBValue( color2 )/2 ), 90);
*/
//		graphics.FillRectangle( &brushTitleBack, 0.0f, 0.0f, (float)iTitleWidth, (float)rectWindow.bottom );

		//graphics.FillRectangle( &lgbrHeading, rectFHeading);
		StringFormat stringFormat;
		//stringFormat.SetAlignment(StringAlignmentCenter);
		//graphics.DrawString(L"Data", -1, &fontHeading, rectFHeading, &stringFormat, &brush);

		stringFormat.SetAlignment(StringAlignmentNear);

		brush.SetColor( (unsigned)Color::Black );
		for(int i=0; i<iValCount; i++ )
		{
            if (strValue[i].GetLength() == 0)
				continue;

			graphics.DrawString(strTitle[i], -1, &fontTitle, rectFTitle, &stringFormat, &brush);

			BSTR str  = strValue[i].AllocSysString();
			graphics.DrawString(str, -1, &fontValue, rectFValue, &stringFormat, &brush);
			SysFreeString( str );

			Pen penLine((unsigned)Color::SlateGray);
			graphics.DrawLine( &penLine, 0.0f, rectFTitle.GetBottom(), (float)rectWindow.right, rectFTitle.GetBottom() );
			rectFTitle.Offset( 0.0f, fCellHeight );
			rectFValue.Offset( 0.0f, fCellHeight );
		} // for(int i=0; i<iValCount; i++ )

		Pen	pen( Color( GetRValue( color2 )/2, GetGValue( color2 )/2, GetBValue( color2 )/2 ) );
		graphics.DrawRectangle( &pen, rectWindow.left, rectWindow.top, rectWindow.right - 1, rectWindow.bottom - 1 );

	} // if( graphics.GetLastStatus() == Ok )

    RedrawWindow();
}

void CPvcsTankValueList::SetTankID(const int& param_iTankID)
{
	m_iTankID = param_iTankID;
}

void CPvcsTankValueList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	GetParent()->PostMessage( WM_LBUTTONDOWN );
	CWnd::OnLButtonDown(nFlags, point);
}

void CPvcsTankValueList::DrawHeading(void)
{
	using namespace Gdiplus;

	Graphics graphics( m_hMemDC );

	if( graphics.GetLastStatus() == Ok )
	{
        CRect rectWindow;
        GetClientRect( &rectWindow );

		SolidBrush brush((unsigned)Color::Beige );
		SolidBrush brushTitleBack((unsigned)Color::Beige );

		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		graphics.SetTextRenderingHint( TextRenderingHintClearTypeGridFit );

		FontFamily  fontFamily(L"Tahoma");
		Gdiplus::Font        fontHeading(&fontFamily, 20, FontStyleBold, UnitPixel);

		RectF		rectFHeading(0.0f, 0.0f, (float)rectWindow.right, fHeadingHeight);

		COLORREF color1 = GetSysColor( COLOR_GRADIENTACTIVECAPTION ), color2 = GetSysColor( COLOR_ACTIVECAPTION );

		LinearGradientBrush lgbrHeading(rectFHeading,
			Color( GetRValue( color1 ), GetGValue( color1 ), GetBValue( color1 ) ),
			Color( GetRValue( color2 )/2, GetGValue( color2 )/2, GetBValue( color2 )/2 ), 90);

		graphics.FillRectangle( &brushTitleBack, 0.0f, 0.0f, (float)iTitleWidth, (float)rectWindow.bottom );
		graphics.FillRectangle( &lgbrHeading, rectFHeading);
		StringFormat stringFormat;
		stringFormat.SetAlignment(StringAlignmentCenter);
		graphics.DrawString(L"Data", -1, &fontHeading, rectFHeading, &stringFormat, &brush);
    }

}

// CPvcsTankDlg message handlers

