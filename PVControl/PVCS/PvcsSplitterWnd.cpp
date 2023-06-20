// PvcsSplitterWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsSplitterWnd.h"
#include ".\pvcssplitterwnd.h"

#include "dxflayout.h"
#include "PvcsTankDlg.h"
#include "pvcsshipview.h"
#include "pvcssplitterlowerwnd.h"


// CPvcsSplitterWnd

IMPLEMENT_DYNAMIC(CPvcsSplitterWnd, CSplitterWnd)
CPvcsSplitterWnd::CPvcsSplitterWnd()
{
}

CPvcsSplitterWnd::~CPvcsSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CPvcsSplitterWnd, CSplitterWnd)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CPvcsSplitterWnd message handlers


void CPvcsSplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CWnd::OnMouseMove(nFlags, point);
}

void CPvcsSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CWnd::OnLButtonDown(nFlags, point);
}

void CPvcsSplitterWnd::ActivateTank(const int& param_iTankID)
{
    CPvcsSplitterLowerWnd  *tempSplitterWnd = dynamic_cast < CPvcsSplitterLowerWnd* > ( GetPane( 1, 0 ) );

    if( tempSplitterWnd )
    {
        CDxfLayout* tempLayout = dynamic_cast < CDxfLayout* > ( tempSplitterWnd->GetPane( 0, 0 )->GetDlgItem( IDC_DXFLAYOUT ) );

        if( tempLayout )
            tempLayout->ActivateTank( param_iTankID );
    } // if( tempSplitterWnd )

}


