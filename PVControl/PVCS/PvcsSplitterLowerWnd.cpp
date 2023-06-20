// PvcsSplitterLowerWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsSplitterLowerWnd.h"
#include ".\pvcssplitterlowerwnd.h"


// CPvcsSplitterLowerWnd

IMPLEMENT_DYNAMIC(CPvcsSplitterLowerWnd, CSplitterWnd)
CPvcsSplitterLowerWnd::CPvcsSplitterLowerWnd()
{
}

CPvcsSplitterLowerWnd::~CPvcsSplitterLowerWnd()
{
}


BEGIN_MESSAGE_MAP(CPvcsSplitterLowerWnd, CSplitterWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CPvcsSplitterLowerWnd message handlers


void CPvcsSplitterLowerWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMouseMove(nFlags, point);
}

void CPvcsSplitterLowerWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}
