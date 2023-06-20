// PvcsControlObjectDlgSpinBox.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsControlObjectDlgSpinBox.h"
#include "pvcsobjectcontroldlg.h"
#include ".\pvcscontrolobjectdlgspinbox.h"
#include "pvcscontrolobjecttimeoutinfo.h"
#include "DxfLayout.h"

// CPvcsControlObjectDlgSpinBox

IMPLEMENT_DYNAMIC(CPvcsControlObjectDlgSpinBox, CEdit)

// Function name   : CPvcsControlObjectDlgSpinBox::CPvcsControlObjectDlgSpinBox
// Description     : Constructor
// Return type     : 
// Argument        : CPvcsControlObject& param_refControlObject

CPvcsControlObjectDlgSpinBox::CPvcsControlObjectDlgSpinBox(CPvcsControlObject& param_refControlObject)
: m_Controller(param_refControlObject)
, m_uiID(0)
{
}


// Function name   : CPvcsControlObjectDlgSpinBox::~CPvcsControlObjectDlgSpinBox
// Description     : Destructor
// Return type     : 

CPvcsControlObjectDlgSpinBox::~CPvcsControlObjectDlgSpinBox()
{
}


BEGIN_MESSAGE_MAP(CPvcsControlObjectDlgSpinBox, CEdit)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CPvcsControlObjectDlgSpinBox message handlers

// Function name   : CPvcsControlObjectDlgSpinBox::Create
// Description     : Creates the spin box with specified attributes
// Return type     : BOOL 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const RECT& param_rect
// Argument        : CWnd* param_pParentWnd
// Argument        : const UINT& param_uiID

BOOL CPvcsControlObjectDlgSpinBox::Create(const CPvcsControlObjectInfo& param_info, 
										  const RECT& param_rect,	
										  CWnd* param_pParentWnd, 
										  const UINT& param_uiID)
{
	m_objectInfo = param_info;

	m_uiID = param_uiID;

	return CEdit::Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 
		param_rect, 
		param_pParentWnd, param_uiID );
}


// Function name   : CPvcsControlObjectDlgSpinBox::OnCreate
// Description     : Message handler
// Return type     : int 
// Argument        : LPCREATESTRUCT lpCreateStruct

int CPvcsControlObjectDlgSpinBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create and initialize the spin control
	UDACCEL accValue[2];

	m_spinCtrl.Create( UDS_ALIGNRIGHT | UDS_SETBUDDYINT | UDS_NOTHOUSANDS , CRect(0, 0, 10, 10), GetParent(), IDC_SPIN );
	

	CString strValue;
	UINT nMin = 0, nMax = 100, nStep = 1;
	m_Controller.GetSpinInitInfo(m_objectInfo, nMin, nMax, nStep, strValue );
	
	CString strValueToBeSet;
	CDxfLayout::GetValueToBeSet(m_objectInfo.GetIndex(),m_objectInfo.GetSubIndex(),strValueToBeSet);
	
	if(strValueToBeSet != "") //if value to be set is not null, then show value. Otherwise show current value
        SetWindowText(strValueToBeSet);
	else
		SetWindowText( strValue );


	accValue[0].nSec  = 0;
	accValue[0].nInc = nStep;
	accValue[1].nSec  = 2;
	accValue[1].nInc = nStep * 5;
	m_spinCtrl.SetAccel( 2, accValue );
	m_spinCtrl.SetRange32(nMin, nMax);
	m_spinCtrl.SetBuddy( this );
	m_spinCtrl.ShowWindow( SW_SHOW );
	return 0;
}


// Function name   : CPvcsControlObjectDlgSpinBox::ChangeValue
// Description     : Tells the controller class to change the value
// Return type     : void 
// Argument        : void

void CPvcsControlObjectDlgSpinBox::ChangeValue(void)
{
	GetWindowText(PreviousSpinCtrlValue);
	SetTimer(1,1000,NULL);
	
	TimeOutInfoSet::iterator it 
			= theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( m_objectInfo.GetIndex(), m_objectInfo.GetSubIndex() ) );

	if( it != theTimeOutInfo().end() )
		((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( false );
}

void CPvcsControlObjectDlgSpinBox::OnTimer(UINT nTimerID)
{
	CString CurrentSpinCtrlValue;

	GetWindowText(CurrentSpinCtrlValue);

	KillTimer(1);

	if(CurrentSpinCtrlValue == PreviousSpinCtrlValue) //if value same, then go for Change Value
	{
	//TRACE("\n\n******************** Go for update Previous = %s  Current = %s\n\n",PreviousSpinCtrlValue,CurrentSpinCtrlValue);	
		// Set to not faulty
		TimeOutInfoSet::iterator it 
			= theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( m_objectInfo.GetIndex(), m_objectInfo.GetSubIndex() ) );

		if( it != theTimeOutInfo().end() )
			((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( false );

		//GetParent()->RedrawWindow();

		//set new value to be set
		CDxfLayout::SetValueToBeSet(m_objectInfo.GetIndex(),m_objectInfo.GetSubIndex(),CurrentSpinCtrlValue);

		// Now tell the controller class to set the value
		if( !m_Controller.OnSetSpin(m_objectInfo, m_uiID, atoi( CurrentSpinCtrlValue ) ) )
		{
			// Set to faulty if failed
			if( it != theTimeOutInfo().end() )
				((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
			GetParent()->RedrawWindow();
		}
	}

}

	
