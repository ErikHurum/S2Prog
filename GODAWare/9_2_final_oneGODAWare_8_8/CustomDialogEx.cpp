// CustomDialogEx.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "CustomDialogEx.h"


// CCustomDialogEx

IMPLEMENT_DYNAMIC(CCustomDialogEx, CDialogEx)

CCustomDialogEx::CCustomDialogEx()
{

}

CCustomDialogEx::~CCustomDialogEx()
{
}


BEGIN_MESSAGE_MAP(CCustomDialogEx, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CCustomDialogEx 消息处理程序



//HBRUSH CCustomDialogEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbrRet = NULL;
//	if (m_brBkgr.GetSafeHandle() != NULL || m_hBkgrBitmap != NULL)
//	{
//#define AFX_MAX_CLASS_NAME 255
//#define AFX_STATIC_CLASS _T("Static")
//#define AFX_BUTTON_CLASS _T("Button")
//		if (nCtlColor == CTLCOLOR_STATIC)
//		{
//			TCHAR lpszClassName[AFX_MAX_CLASS_NAME + 1];
//			int nChars = ::GetClassName(pWnd->GetSafeHwnd(), lpszClassName, AFX_MAX_CLASS_NAME);

//			if ( ( nChars > 0 )
//				&& ( ( _tcsncmp( lpszClassName, AFX_STATIC_CLASS, nChars ) == 0 )
//				|| ( _tcsncmp( lpszClassName, AFX_BUTTON_CLASS, nChars ) == 0 )
//				)
//				)
//			{
//				pDC->SetBkMode(TRANSPARENT);
//				hbrRet = (HBRUSH)m_brBkgr;
//			}
//		}
//	}
//	else
//		hbrRet = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

//	return hbrRet;
//}

void CCustomDialogEx::DoDataExchange(CDataExchange* pDX)
{


	CDialogEx::DoDataExchange(pDX);
}


void CCustomDialogEx::OnOK()
{

}


void CCustomDialogEx::OnCancel()
{

}
