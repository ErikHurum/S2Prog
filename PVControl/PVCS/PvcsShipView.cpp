// PvcsShipView.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsShipView.h"
#include ".\pvcs v1.0.h"
// CPvcsShipView

IMPLEMENT_DYNCREATE(CPvcsShipView, CView)

CPvcsShipView::CPvcsShipView()
{

}

CPvcsShipView::~CPvcsShipView()
{
}

BEGIN_MESSAGE_MAP(CPvcsShipView, CView)
    ON_WM_CREATE()
END_MESSAGE_MAP()


// CPvcsShipView drawing

void CPvcsShipView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: add draw code here
}


// CPvcsShipView diagnostics

#ifdef _DEBUG
void CPvcsShipView::AssertValid() const
{
    CView::AssertValid();
}

void CPvcsShipView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}
#endif //_DEBUG


// CPvcsShipView message handlers

int CPvcsShipView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect( &rect );
    //CPoint TopLeft = rect.TopLeft();
    //CPoint BottomRight = rect.BottomRight();
    //rect.SetRect(TopLeft.x,TopLeft.y,BottomRight.x+1000,BottomRight.y+500);

    //rect.right += 500;
    m_dxfShipLayout.Create( rect, this );
    //

	bool hasLineCol  = true;
	bool hasTextCol  = true;
	bool hasBKCol    = true;
	bool HasScrCol	 = true;
	int  ScrColor    = theConfiguration().GetScreenColor(CPVCSApp::ScreenIndex,&HasScrCol);
	int  LineCol     = theConfiguration().GetScreenLineColor(CPVCSApp::ScreenIndex,&hasLineCol);
	int  TextCol     = theConfiguration().GetScreenTextColor(CPVCSApp::ScreenIndex,&hasTextCol);
    int  BKCol       = theConfiguration().GetScreenBckGndColor(CPVCSApp::ScreenIndex,&hasBKCol);

	m_dxfShipLayout.Open(theConfiguration().GetScreenFile(CPVCSApp::ScreenIndex),theConfiguration().GetScreenTankLayer(CPVCSApp::ScreenIndex),true, ScrColor,BKCol,LineCol,TextCol,hasLineCol, hasTextCol, hasBKCol);
    m_dxfShipLayout.EnableDraw();

    return 0;
}
