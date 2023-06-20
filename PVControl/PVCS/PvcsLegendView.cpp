// PvcsLegendView.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsLegendView.h"
#include ".\pvcslegendview.h"

#include "resource.h"

// CPvcsLegendView

IMPLEMENT_DYNCREATE(CPvcsLegendView, CView)

CPvcsLegendView::CPvcsLegendView()
{
	m_ptrTankMap = NULL;
    SplitScreens = theConfiguration().GetSplitScreens();
}

CPvcsLegendView::~CPvcsLegendView()
{
}

BEGIN_MESSAGE_MAP(CPvcsLegendView, CView)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPvcsLegendView drawing

void CPvcsLegendView::OnDraw(CDC* pDC)
{
}


// CPvcsLegendView diagnostics

#ifdef _DEBUG
void CPvcsLegendView::AssertValid() const
{
	CView::AssertValid();
}

void CPvcsLegendView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

// CPvcsLegendView message handlers


// Function name   : CPvcsLegendView::OnCreate
// Description     : Message Handler for WM_CREATE
// Return type     : int 
// Argument        : LPCREATESTRUCT lpCreateStruct

int CPvcsLegendView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect( &rect );
    
	// Create the Legend Window
	m_wndLegend.Create(NULL, "", WS_CHILD|WS_VISIBLE /*| WS_VSCROLL*/, rect, this, IDC_LEGENDLIST);
	m_wndLegend.ShowWindow( SW_SHOW );

	return 0;
}

void CPvcsLegendView::SetTankMap(CPvcsShipData::TankMap *pTankMap)
{
	m_ptrTankMap = pTankMap;
	if(m_ptrTankMap == NULL)
		m_ptrTankMap = theShipData().m_DefaultTankMap;
	m_wndLegend.SetTankMap(m_ptrTankMap);
}