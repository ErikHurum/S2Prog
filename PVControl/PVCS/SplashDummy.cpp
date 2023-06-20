// SplashDummy.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "SplashDummy.h"
#include ".\splashdummy.h"

#include "splashwnd.h"


// CSplashDummy

IMPLEMENT_DYNAMIC(CSplashDummy, CWnd)
CSplashDummy::CSplashDummy()
: m_nSecLeft(0)
, m_nSec(10)
{
}

CSplashDummy::~CSplashDummy()
{
}


BEGIN_MESSAGE_MAP(CSplashDummy, CWnd)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_CREATE()
//	ON_WM_TIMER()
END_MESSAGE_MAP()



// CSplashDummy message handlers


void CSplashDummy::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// suppress compiler warning
	nFlags;
	nRepCnt;

#ifdef _DEBUG
	if( nChar == VK_F2 || nChar == VK_F11 )
	{
#else
	if( nChar == VK_F12)
	{
#endif
		CSplashWnd* tempWnd = dynamic_cast <CSplashWnd*> ( GetParent() );

		if( tempWnd )
			if( nChar == VK_F2 )
				tempWnd->OnOK();
			else
				tempWnd->OnCancel();
	} // if( nChar == VK_F12)
}

void CSplashDummy::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	Draw();
}
#pragma warning (disable: 4244 4245)

void CSplashDummy::Draw(void)
{
	using namespace Gdiplus;

	CRect rectWnd;
	GetClientRect( &rectWnd );

	Graphics graphics( m_hWnd );

	if( graphics.GetLastStatus() == Ok )
	{
		graphics.SetSmoothingMode( SmoothingModeHighQuality );
		graphics.SetTextRenderingHint( TextRenderingHintClearTypeGridFit );

		FontFamily  fontFamily(L"Tahoma");
		Gdiplus::Font   font(&fontFamily, 15, FontStyleRegular, UnitPixel);
		Gdiplus::Font	mainFont( &fontFamily, 40, FontStyleBold, UnitPixel);
		Pen progPen(Color::DarkKhaki);
		SolidBrush txtBrush( Color::MidnightBlue );
		RectF	progRect( 10.0f, (REAL)rectWnd.Height() - 30.0f, (REAL)rectWnd.Width() - 20.0f, 20.0f );
		RectF	mainRect(0, 0, rectWnd.Width(), rectWnd.Height() );
		LinearGradientBrush progBrush( progRect, Color::LawnGreen,Color::Crimson, 180.0 );
		LinearGradientBrush mainBrush( mainRect, Color::Peru, Color::Moccasin, 90.0 );
		SolidBrush progBack( Color::PaleGoldenrod );
		StringFormat stringFormat;

		graphics.SetTextRenderingHint( TextRenderingHintClearTypeGridFit );
		graphics.FillRectangle( &mainBrush, mainRect );
		graphics.FillRectangle( &progBack, progRect );
		graphics.FillRectangle( &progBrush, progRect.X, progRect.Y,
			( progRect.Width * ( m_nSec - m_nSecLeft) ) / (float)m_nSec, progRect.Height );


		mainRect.Inflate( - 20, -20 );
		stringFormat.SetAlignment(StringAlignmentCenter);

		graphics.DrawString(L"Pump and Valve Control System", -1, &mainFont, mainRect, &stringFormat, &txtBrush);
		CString strText;
		strText.Format("PVCS will be loaded in %d seconds", m_nSecLeft );
		BSTR str = strText.AllocSysString();
		graphics.DrawString(str, -1, &font, progRect, &stringFormat, &txtBrush);
		SysFreeString( str );

#ifdef _DEBUG
		strText.Format("Press F11 to exit..." );
#else
		strText.Format("Press F12 to exit..." );
#endif

		str = strText.AllocSysString();
		graphics.DrawString( str, -1, &font, PointF( 10.0f, (REAL)rectWnd.Height() - 50.0f), &txtBrush );
		SysFreeString( str );

		graphics.DrawRectangle( &progPen, progRect );

	} // if( graphics.GetLastStatus() == Ok )
}

int CSplashDummy::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	Draw();
	m_nSecLeft = m_nSec;
	return 0;
}
