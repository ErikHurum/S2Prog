// SplashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "SplashWnd.h"
#include ".\splashwnd.h"


// CSplashWnd dialog

IMPLEMENT_DYNAMIC(CSplashWnd, CDialog)
CSplashWnd::CSplashWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CSplashWnd::IDD, pParent)
	, m_nSec(10)
{
}

CSplashWnd::~CSplashWnd()
{
}

void CSplashWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSplashWnd, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSplashWnd message handlers

BOOL CSplashWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetClientRect( &rect );

	CString strTitle;

	if( !strTitle.LoadString( IDS_TITLE_SPLASH ) )
		strTitle.Format( "Starting up PVCS" );

	SetWindowText( strTitle );

	SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

	m_wndDummy.Create( NULL, "", WS_CHILD|WS_VISIBLE, rect, this, 1);
	m_wndDummy.ShowWindow( SW_SHOW );
	m_wndDummy.PostMessage( WM_LBUTTONDOWN );
	m_wndDummy.PostMessage( WM_LBUTTONUP );

	SetTimer( IDT_SPLASHPROGRESS, 1000, NULL );
	SetTimer( IDT_CLOSESPLASH, m_nSec * 1000, NULL );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSplashWnd::OnTimer(UINT nIDEvent)
{
	if( nIDEvent == IDT_CLOSESPLASH )
		OnOK();

	if( nIDEvent == IDT_SPLASHPROGRESS )
	{
		CSplashDummy* wndDummy = dynamic_cast <CSplashDummy*> ( GetDlgItem( 1 ) );

		if( wndDummy )
		{
			wndDummy->m_nSecLeft--;
			wndDummy->RedrawWindow();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CSplashWnd::OnCancel()
{
	CDialog::OnCancel();
}

void CSplashWnd::OnOK(void)
{
	CDialog::OnOK();
}
