// PvcsTankView.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsTankView.h"
#include ".\pvcstankview.h"
#include ".\pvcs v1.0.h"

// CPvcsTankView

IMPLEMENT_DYNCREATE(CPvcsTankView, CView)

CPvcsTankView::CPvcsTankView()
: m_bShowRightSide(false)
,ScaleX(1.0)
,ScaleY(1.0)
{
    m_ptrTankMap = NULL;
    SplitScreens = theConfiguration().GetSplitScreens();

}

CPvcsTankView::~CPvcsTankView()
{
    for ( int i=0; i<( int )m_dlgTankArray.size(); i++ )
        delete m_dlgTankArray[i];
}

BEGIN_MESSAGE_MAP(CPvcsTankView, CView)
ON_WM_CREATE()
END_MESSAGE_MAP()


// CPvcsTankView drawing

void CPvcsTankView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: add draw code here
}


// CPvcsTankView diagnostics

#ifdef _DEBUG
void CPvcsTankView::AssertValid() const
{
    CView::AssertValid();
}

void CPvcsTankView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}
#endif //_DEBUG


// CPvcsTankView message handlers

BOOL CPvcsTankView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    // TODO: Add your specialized code here and/or call the base class

    return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CPvcsTankView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}

bool CPvcsTankView::AddTank(const int& param_iTankID)
{
    bool bSuccess = false;

    CPvcsTankDlg* tempTankDlg = new CPvcsTankDlg;
    m_dlgTankArray.push_back( tempTankDlg );

    if (m_ptrTankMap == NULL)
        m_ptrTankMap = theShipData().m_DefaultTankMap;
    double tmpScaleX = theConfiguration().GetScaleX( param_iTankID );
    double tmpScaleY = theConfiguration().GetScaleY( param_iTankID );
	bool hasLineCol  = true;
	bool hasTextCol  = true;
	bool hasBKCol    = true;
	int  LineCol     = theConfiguration().GetLineColor(param_iTankID, &hasLineCol);
	int  TextCol     = theConfiguration().GetTextColor(param_iTankID, &hasTextCol);
    int  BKCol       = theConfiguration().GetBackGroundColor(param_iTankID, &hasBKCol);

    if ( tempTankDlg->Create( theConfiguration().GetTankFile( param_iTankID ), theConfiguration().GetScreenTankLayer(CPVCSApp::ScreenIndex),
                              tmpScaleX,tmpScaleY, BKCol, theConfiguration().GetUndefObjectColor(param_iTankID),theConfiguration().GetObjectColor( param_iTankID ), LineCol, TextCol, hasLineCol, hasTextCol, hasBKCol, param_iTankID,this) ) {
        tempTankDlg->SetWindowText( theConfiguration().GetTankName( param_iTankID ) );
        bSuccess = true;
        ScaleX = max(ScaleX,tmpScaleX);
        ScaleY = max(ScaleY,tmpScaleY);

    } // if ( m_dlgDemoTank->Create( theConfiguration().GetTankFile( param_iTankID ), theConfiguration().GetTankLayer(), param_iTankID, this ) )

    return bSuccess;
}

void CPvcsTankView::ShowTank(const int& param_iTankID)
{
    int nCount = static_cast<int> (m_dlgTankArray.size());
    if (SplitScreens>1) {
        CRect rectWindow;
        GetClientRect( &rectWindow );

        if ( ScaleX == 1.0 && ScaleY == 1.0 ) {
            rectWindow.right = rectWindow.Width() / 2;
            if ( m_bShowRightSide ) {
                rectWindow.OffsetRect( rectWindow.Width(), 0  );
                m_bShowRightSide = false;
            } // if( m_bShowRightSide )
            else{
                m_bShowRightSide = true;
            }

        }

        for (int i=0; i<nCount; i++) {
            if ( param_iTankID == m_dlgTankArray[i]->GetTankID() ) {
                m_dlgTankArray[i]->SetActive();
                m_dlgTankArray[i]->SetUpdate( true );

                if ( m_dlgTankArray[i]->m_bChangePos )
                    m_dlgTankArray[i]->MoveWindow( &rectWindow );
                m_dlgTankArray[i]->m_bChangePos = true;
                m_dlgTankArray[i]->SetWindowPos( &wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
            } // if( param_iTankID == m_dlgTankArray[i].GetTankID() )
            else
                m_dlgTankArray[i]->SetActive( false );

        } // for(int i=0; i<nCount; i++)
    }else{
        CRect rectWindow;
        GetClientRect( &rectWindow );
        if ( ScaleX == 1.0 && ScaleY == 1.0 ) {
            rectWindow.right = rectWindow.Width() / 2;
            if ( m_bShowRightSide ) {
                rectWindow.OffsetRect( rectWindow.Width(), 0  );
                m_bShowRightSide = false;
            } // if( m_bShowRightSide )
            else{
                m_bShowRightSide = true;
            }

        }

        for (int i=0; i<nCount; i++) {
            if ( param_iTankID == m_dlgTankArray[i]->GetTankID() ) {
                m_dlgTankArray[i]->SetActive( true );
                m_dlgTankArray[i]->SetUpdate( true );

                if ( m_dlgTankArray[i]->m_bChangePos )
                    m_dlgTankArray[i]->MoveWindow( &rectWindow );
                m_dlgTankArray[i]->m_bChangePos = true;
                m_dlgTankArray[i]->SetWindowPos( &wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
            } // if( param_iTankID == m_dlgTankArray[i].GetTankID() )
            else{
                m_dlgTankArray[i]->SetActive( false );
                m_dlgTankArray[i]->SetUpdate( false );
			}

        } // for(int i=0; i<nCount; i++)
    }
}

void CPvcsTankView::Update(CPvcsShipData::TankMap *pTankMap)
{

    int nCount = static_cast<int> (m_dlgTankArray.size());

    m_ptrTankMap = pTankMap;
    if (m_ptrTankMap == NULL)
        m_ptrTankMap = theShipData().m_DefaultTankMap;

    //set new data map for the tank dlg
    CPvcsTankDlg::m_ptrTankMap = m_ptrTankMap;
    if ( ScaleX == 1.0 && ScaleY == 1.0 ) {
        for (int i=0; i<nCount; i++) {
            if ( m_dlgTankArray[i]->MustUpdate() ) {
                //m_dlgTankArray[i]->RedrawWindow();
                CPvcsTankValueList *tempValueWnd = dynamic_cast <CPvcsTankValueList*> ( m_dlgTankArray[i]->GetDlgItem( IDC_TANKVALUELIST ) );
                CDxfLayout *tempLayoutWnd = dynamic_cast <CDxfLayout*> ( m_dlgTankArray[i]->GetDlgItem( IDC_DXFLAYOUT ) );

                if ( tempValueWnd )
                    tempValueWnd->Draw(m_ptrTankMap);

                if ( tempLayoutWnd )
                    tempLayoutWnd->Update(m_ptrTankMap,-1,false);

            } // if( m_dlgTankArray[i]->MustUpdate() )

        } // for(int i=0; i<nCount; i++)
    }else{
        for (int i=0; i<nCount; i++) {
            if ( m_dlgTankArray[i]->MustUpdate() ) {
                //m_dlgTankArray[i]->RedrawWindow();
                CDxfLayout *tempLayoutWnd = dynamic_cast <CDxfLayout*> ( m_dlgTankArray[i]->GetDlgItem( IDC_DXFLAYOUT ) );
                if ( tempLayoutWnd )
                    tempLayoutWnd->Update(m_ptrTankMap,-1,false);

            } // if( m_dlgTankArray[i]->MustUpdate() )

        } // for(int i=0; i<nCount; i++)
    }
}
