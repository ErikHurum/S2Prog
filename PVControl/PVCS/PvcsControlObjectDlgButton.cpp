// PvcsControlObjectDlgButton.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsControlObjectDlgButton.h"
#include "pvcscontrolobjecttimeoutinfo.h"
#include "dxflayout.h"
#include "pvcsobjectcontroldlg.h"

// CPvcsControlObjectDlgButton

IMPLEMENT_DYNAMIC(CPvcsControlObjectDlgButton, CButton)

// Function name   : CPvcsControlObjectDlgButton::CPvcsControlObjectDlgButton
// Description     : 
// Return type     : 
// Argument        : CPvcsControlObject& param_refControlObject

CPvcsControlObjectDlgButton::CPvcsControlObjectDlgButton(CPvcsControlObject& param_refControlObject)
: m_Controller(param_refControlObject)
, m_uiID(0)
, m_bButtonDown(false)
{
}


// Function name   : CPvcsControlObjectDlgButton::~CPvcsControlObjectDlgButton
// Description     : 
// Return type     : 

CPvcsControlObjectDlgButton::~CPvcsControlObjectDlgButton()
{
	if( m_bButtonDown )
		m_Controller.OnButton( m_objectInfo, m_uiID, false );
}


BEGIN_MESSAGE_MAP(CPvcsControlObjectDlgButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CPvcsControlObjectDlgButton message handlers



// Function name   : CPvcsControlObjectDlgButton::Create
// Description     : Creates the button with specified attributes
// Return type     : BOOL 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const RECT& param_rect
// Argument        : CWnd* param_pParentWnd
// Argument        : const UINT& param_uiID

BOOL CPvcsControlObjectDlgButton::Create(const CPvcsControlObjectInfo& param_info, 
										 const RECT& param_rect, 
										 CWnd* param_pParentWnd,  
										 const UINT& param_uiID)
{
	m_objectInfo = param_info;

	m_uiID = param_uiID;
	return CButton::Create(param_info.GetButtonCaption( param_uiID ),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
		param_rect, 
		param_pParentWnd, param_uiID );
}


// Function name   : CPvcsControlObjectDlgButton::OnLButtonDown
// Description     : Message handler
// Return type     : void 
// Argument        : UINT nFlags
// Argument        : CPoint point

void CPvcsControlObjectDlgButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_bButtonDown = true;

	int iIndex;
	int iSubIndex;

	iIndex = m_objectInfo.GetIndex();
	iSubIndex = m_objectInfo.GetSubIndex();

	CButton::OnLButtonDown(nFlags, point);

	// Set the object as not faulty
	TimeOutInfoSet::iterator it 
		= theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo(iIndex,iSubIndex));

	if( it != theTimeOutInfo().end() )
		((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( false );

	CString strClassName = "";
	strClassName = m_objectInfo.GetClassName();

	if(strClassName.MakeLower() == "cpvcscontrolobjectthrottlevalve" 
		|| strClassName.MakeLower() == "cpvcscontrolobjectcargovalve"// for throttle and cargo controls
		|| strClassName.MakeLower() == "cpvcscontrolobjectcargovalve2")
	{
		//Set spin value
		CString strButtonCaption = "";
		GetWindowText(strButtonCaption);
		int iValueToSet = atoi(strButtonCaption);

		strButtonCaption.Format("%d",iValueToSet);

		//if spin ctrl then set value
		theController().SetValueToSpinCtrl(strButtonCaption);

		m_Controller.OnButton( m_objectInfo, m_uiID, true );

	//	TRACE("\n\n\nButton - wait for Access\n\n\n");
	//	//wait for access
	//	while(CDxfLayout::GetThreadBusyState(iIndex,iSubIndex))
	//		Sleep(0);

	//	//get Access
	//	CDxfLayout::SetThreadBusyState(iIndex,iSubIndex,true);
	//	TRACE("\n\n\nButton - Get Access\n\n\n");

	//	//Check that thread runnning or not
	//	if(CDxfLayout::GetThreadRunningState(iIndex,iSubIndex))
	//	{
	//		TRACE("\n\n\nButton - wait for thread to end\n\n\n");
	//		CDxfLayout::SetThreadExitState(iIndex,iSubIndex,true);
	//		while(!CDxfLayout::GetThreadExitedState(iIndex,iSubIndex))
	//			Sleep(0);//wait for thread to end
	//	}

	//	TRACE("\n\n\nButton - wait for thread over\n\n\n");
	//	//Reset parameter for new thread
	//	CDxfLayout::SetThreadRunningState(iIndex,iSubIndex,true);
	//	CDxfLayout::SetThreadExitState(iIndex,iSubIndex,false);
	//	CDxfLayout::SetThreadExitedState(iIndex,iSubIndex,false);

	//	//Set spin value
	//	CString strButtonCaption = "";
	//	GetWindowText(strButtonCaption);
	//	int iValueToSet = atoi(strButtonCaption);

	//	strButtonCaption.Format("%d",iValueToSet);
	//	
	//	//if spin ctrl then set value
	//	if(theController().SetValueToSpinCtrl(strButtonCaption))
	//	{
	//		//set new value to be set
	//		CDxfLayout::SetValueToBeSet(iIndex,iSubIndex,strButtonCaption);
	//	}

	//	//Create Thread
	//
	//	CWinThread *pThread = AfxBeginThread(DlgButtonDownThread, this,THREAD_PRIORITY_ABOVE_NORMAL);
	//TRACE("\n\n\nButton - new thread start = %x\n\n\n",pThread->m_nThreadID);

	}
	else{ //for other controls
		CWinThread *pThread = AfxBeginThread(DlgButtonDownThread, this,THREAD_PRIORITY_ABOVE_NORMAL);
	}

}


// Function name   : CPvcsControlObjectDlgButton::OnLButtonUp
// Description     : Message Handler
// Return type     : void 
// Argument        : UINT nFlags
// Argument        : CPoint point

void CPvcsControlObjectDlgButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bButtonDown = false;
	ReleaseCapture();

	CButton::OnLButtonUp(nFlags, point);

	TimeOutInfoSet::iterator it 
		= theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( m_objectInfo.GetIndex(), m_objectInfo.GetSubIndex() ) );

	if( !m_Controller.OnButton( m_objectInfo, m_uiID, false ) )
	{
		// Set as faulty if error occured
		if( it != theTimeOutInfo().end() )
			((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );
		
		GetParent()->RedrawWindow();
	}else
		GetParent()->RedrawWindow();
}


//Add by  , to return Private Data
CPvcsControlObject* CPvcsControlObjectDlgButton::Get_CPvcsControlObject(void)
{
	return &(m_Controller);
}

//Add by  , to return Private Data
UINT CPvcsControlObjectDlgButton::Get_uID(void)
{
	return m_uiID;
}

//Add by  , to return Private Data
CPvcsControlObjectInfo CPvcsControlObjectDlgButton::Get_CPvcsControlObjectInfo(void)
{
	return m_objectInfo;
}


//	Code Add By		:  
//	Date & Time		: 16:Feb:2007 1.25 PM 
//	Function Name	: UINT DlgButtonDownThread(LPVOID param)
//	Description		: Thread Procedure, invoke on left click on Button Control. 
//	Argument		: LPVOID *
//	Return Type		: UINT
//	Called From		: void CPvcsControlObjectDlgButton::OnLButtonDown(UINT nFlags, CPoint point)
#pragma warning (disable: 4101)
UINT DlgButtonDownThread(LPVOID param)
{
	TRACE("\n\n\nButton Thread Started\n\n\n");

	CPvcsControlObjectDlgButton *PvcsControlObjectDlgButton_ptr = (CPvcsControlObjectDlgButton*)param;
	CPvcsControlObjectInfo PvcsControlObjectInfo = PvcsControlObjectDlgButton_ptr->Get_CPvcsControlObjectInfo();
	CPvcsControlObject * PvcsControlObject_var = PvcsControlObjectDlgButton_ptr->Get_CPvcsControlObject();

	int iIndex = PvcsControlObjectInfo.GetIndex();
	int iSubIndex = PvcsControlObjectInfo.GetSubIndex();
	int iButtonID = PvcsControlObjectDlgButton_ptr->Get_uID();

	try
	{
		// Set the object as not faulty
		TimeOutInfoSet::iterator it 
			= theTimeOutInfo().find( CPvcsControlObjectTimeOutInfo( iIndex,iSubIndex ) );

		TRACE("\n\n\nButton Thread inside - 1\n\n\n");
		if( it != theTimeOutInfo().end() )
			((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( false );

		TRACE("\n\n\nButton Thread inside - 2\n\n\n");
	
		if (!(PvcsControlObject_var->OnButton(PvcsControlObjectInfo,iButtonID,true)))
		{
			// Set as faulty if error occured
			if( it != theTimeOutInfo().end() )
				((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut( true );

			if(theController().m_hWnd)	
				theController().Draw();
			TRACE("\n\n\nButton Thread inside - 3\n\n\n");

		}
	}
	catch (exception &e)
	{
		TRACE("\n\n\nButton Thread catch Ended\n\n\n");
	}

	TRACE("\n\n\nButton Thread Ended\n\n\n");
	return 0;
}

