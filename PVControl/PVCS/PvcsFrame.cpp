// PvcsFrame.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsFrame.h"
#include ".\pvcsframe.h"

#include "resource.h"

#include "pvcstankview.h"
#include "pvcsscreenView.h"
#include "pvcslegendview.h"
#include "PVCS v1.0.h"
#include "PvcsScreenInfo.h"
#include "emgbuttonoperation.h"
#include "PumpButtonoperation.h"




//CMenu * CPvcsFrame::MainMenu = NULL;

// CPvcsFrame
IMPLEMENT_DYNCREATE(CPvcsFrame, CFrameWnd)


// Function name   : CPvcsFrame::CPvcsFrame
// Description     : Default constructor
// Return type     :

CPvcsFrame::CPvcsFrame() {
	m_ptrTankMap = NULL;
	SplitScreens = theConfiguration().GetSplitScreens();
}


// Function name   : CPvcsFrame::~CPvcsFrame
// Description     : Destructor
// Return type     :

CPvcsFrame::~CPvcsFrame() {
	//TRACE("\nCPvcsFrame-Destuctor");
}


// Message Maps

BEGIN_MESSAGE_MAP(CPvcsFrame, CFrameWnd)
ON_MESSAGE(WM_UPDATE_VALUES, OnUpdateValues)
ON_WM_CREATE()
ON_WM_SIZE()
ON_WM_NCMOUSEMOVE()
ON_BN_CLICKED(IDC_ALARMBUTTON , OnBnClickedAlarmbutton)
ON_BN_CLICKED(IDC_PUMPBUTTON1, OnBnClickedPumpButton1)
ON_BN_CLICKED(IDC_PUMPBUTTON2, OnBnClickedPumpButton2)
ON_BN_CLICKED(IDC_PUMPBUTTON3, OnBnClickedPumpButton3)
ON_BN_CLICKED(IDC_PUMPBUTTON4, OnBnClickedPumpButton4)
ON_BN_CLICKED(IDC_PUMPBUTTON5, OnBnClickedPumpButton5)
END_MESSAGE_MAP()



// Function name   : CPvcsFrame::OnCreateClient
// Description     : Overridden function
// Return type     : BOOL
// Argument        : LPCREATESTRUCT lpcs
// Argument        : CCreateContext* pContext

BOOL CPvcsFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext) {
	int iTopHeight;
	int iBottomHeight;
	int iLeftWidth;
	int iRightWidth;

	CRect cr;
	CString strTitle;
	GetClientRect(&cr);

	if (SplitScreens == 2) {
		// Calculate the metrics for various panes
		iTopHeight = 2 * cr.Height() / 3;
		iBottomHeight = cr.Height() - iTopHeight;

		iLeftWidth = 17 * cr.Width() / 20;
		iRightWidth = cr.Width() - iLeftWidth;
	} else {
		iTopHeight = 9 * cr.Height() / 10;
		iBottomHeight = cr.Height() - iTopHeight;

		iLeftWidth = 17 * cr.Width() / 20;
		iRightWidth = cr.Width() - iLeftWidth;
	}

	// The main splitter window
	if (!m_wndSplitter.CreateStatic(this, 2, 1, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN)) return false;

	// The upper tank view
	if (!m_wndSplitter.CreateView(0, 0,
								  RUNTIME_CLASS(CPvcsTankView),
								  CSize(cr.Width(), iTopHeight), pContext)) return false;

	// the lower splitter window
	if (!m_wndLowerSplitter.CreateStatic(&m_wndSplitter, 1, 2,
										 WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(1, 0))) return false;
	//CString Command_Value = theShipData().GetSysConfig().GetMasterIP();

	if (!m_wndLowerSplitter.CreateView(0, 0,
									   RUNTIME_CLASS(CPvcsScreenView), CSize(iLeftWidth, iBottomHeight), pContext)) return false;
	if (!m_wndLowerSplitter.CreateView(0, 1,
									   RUNTIME_CLASS(CPvcsLegendView), CSize(iRightWidth, iBottomHeight), pContext)) return false;

	return true;
}


// Function name   : CPvcsFrame::PreCreateWindow
// Description     : Overridden Class
// Return type     : BOOL
// Argument        : CREATESTRUCT& cs

BOOL CPvcsFrame::PreCreateWindow(CREATESTRUCT &cs) {
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	// If this is ballast frame in Main PVCS, open it in the second monitor
	if (theApp.IsBackupMode || CPVCSApp::ScreenIndex == 1) cs.x = 0;
	else cs.x = cx;

	cs.y = 0;
	cs.cx = cx;
	cs.cy = cy;

	// Disable Maximize/Restore Button
	cs.style |= WS_MAXIMIZE;
	cs.style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

	// If Main PVCS, disable Minimize Button
	if (!theApp.IsBackupMode) cs.style &= ~(WS_MINIMIZEBOX);

	return CFrameWnd::PreCreateWindow(cs);
}

afx_msg LRESULT CPvcsFrame::OnUpdateValues(WPARAM wParam, LPARAM lParam) {
	return NULL;
}


// Function name   : CPvcsFrame::UpdateValues
// Description     : Updates the values for from the tank data
// Return type     : void
// Argument        : void

void CPvcsFrame::UpdateValues(void) {

	// Get the tank view
	CPvcsTankView *tempTankView = dynamic_cast<CPvcsTankView *>(m_wndSplitter.GetPane(0, 0));
	// get the current scroll positions for correct paint operations

	// Update the tank view
	if (tempTankView) {

		tempTankView->Update(m_ptrTankMap);
	}
	// Get the Ship layout
	CDxfLayout *tempLayout = dynamic_cast<CDxfLayout *>(m_wndLowerSplitter.GetPane(0, 0)->GetDlgItem(IDC_DXFLAYOUT));

	// Update the ship layout
	if (tempLayout) tempLayout->Update(m_ptrTankMap, ScreenNumber, false); // EHSMark, was false
																		   // Get the Legend View
	CPvcsLegendView *tempLegendView = dynamic_cast<CPvcsLegendView *>(m_wndLowerSplitter.GetPane(0, 1));

	// Update the legend view
	if (tempLegendView) {
		tempLegendView->SetTankMap(m_ptrTankMap);
		tempLegendView->GetDlgItem(IDC_LEGENDLIST)->RedrawWindow();
	}
}

// Function name   : CPvcsFrame::OnCreate
// Description     : Message Handler for WM_CREATE
// Return type     : int
// Argument        : LPCREATESTRUCT lpCreateStruct
#pragma warning (disable: 4800)
int CPvcsFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;

	// Get the system menu
	CMenu *pTopMenu = GetSystemMenu(FALSE);

	// Remove the unwanted options from the menu
	pTopMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);  // Maximize/Restore
	pTopMenu->RemoveMenu(SC_SIZE, MF_BYCOMMAND);      // Resize
	pTopMenu->RemoveMenu(SC_MOVE, MF_BYCOMMAND);      // Move

	CMenu *MainMenu;
	MainMenu = GetMenu();
	if (MainMenu != NULL) {
		for (int i = 1; i <= CPVCSApp::ScreenCount; i++) {
			//if same screen, then its menu should be default
			if (ScreenNumber == i) {
				MainMenu->AppendMenu(MF_STRING, SCREENMENUID + i, theConfiguration().GetScreenTitle(i));
				MainMenu->SetDefaultItem(SCREENMENUID + i);
			} else MainMenu->AppendMenu(MF_STRING, SCREENMENUID + i, theConfiguration().GetScreenTitle(i));
		}
	}

	m_PvcsToolBar.CreateEx(this, TBSTYLE_FLAT /*| BTNS_CHECK*/, WS_CHILD | WS_VISIBLE | CBRS_TOP);
	m_PvcsToolBar.LoadToolBar(IDR_PVCSTOOLBAR);
	m_PvcsToolBar.ShowWindow(SW_SHOW);

	int iToolBarItemindex = 0;
	while (m_PvcsToolBar.GetItemID(iToolBarItemindex) != IDT_ALARM) iToolBarItemindex++;

	m_PvcsToolBar.SetButtonInfo(iToolBarItemindex,IDT_ALARM, TBBS_BUTTON, iToolBarItemindex);

	CRect ItemRect;
	m_PvcsToolBar.GetItemRect(iToolBarItemindex, &ItemRect);

	ItemRect.left += 2;
	ItemRect.right += 120;
	m_PvcsToolBar.m_pPvcsToolBarAlarmButton = new CPvcsToolBarAlarmButton("No Alarm", ItemRect);
	m_PvcsToolBar.m_pPvcsToolBarAlarmButton->Create(NULL, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | BS_MULTILINE, ItemRect, &m_PvcsToolBar, IDC_ALARMBUTTON);
	m_PvcsToolBar.m_pPvcsToolBarAlarmButton->SetColor(RGB(255, 255, 255), RGB(0, 147, 0), "No Alarm");

	//Extra gap between Alarm button and other buttons like e.g. Emergency Button
	ItemRect.left = ItemRect.right + 2;
	ItemRect.right = ItemRect.left + 130;
	/*
	{
		CPvcsToolBarPumpButton *ObjTempButton = new CPvcsToolBarPumpButton("PumpControl", ItemRect);
		//CPvcsToolBarAlarmButton *ObjTempButton = new CPvcsToolBarAlarmButton("No Alarm", ItemRect);
		ObjTempButton->Create("Test", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | BS_MULTILINE, ItemRect, &m_PvcsToolBar, IDC_PUMPBUTTON1);
		ObjTempButton->SetColor(RGB(255, 255, 255), RGB(0, 147, 0), "No Alarm");
		ItemRect.left = ItemRect.right + 2;
		ItemRect.right = ItemRect.left + 130;
	}
	*/
	/* First we start witht the emergency buttons */
	{
		UINT uiEmgButtonCount = CEmgButtonOperation::m_EmgButtonInfo.size();

		for (unsigned i = 0; i < uiEmgButtonCount; i++) {
			int iButtonID = 0;
			CPvcsToolBarEmgButton *ObjTempButton = new CPvcsToolBarEmgButton;

			CString strButtonText = theConfiguration().GetEmgButtonText(i);
			CString strButtonToolTipText = theConfiguration().GetEmgButtonTooltip(i);
			iButtonID = SCREENMENUID + CPVCSApp::ScreenCount + i + 1;
			int iButtonIndex = i;
			CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->strButtonText   = strButtonText;
			CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->bInvertInput    = theConfiguration().GetEmgObjInputInvert(iButtonIndex);
			CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->iInputType      = theConfiguration().GetEmgObjInputType(iButtonIndex);
			CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->dInputThreshold = theConfiguration().GetEmgObjInputThreshold(iButtonIndex);

			CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->iWagoChNo       = theConfiguration().GetWagoInputEmgChNo(iButtonIndex);
			CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->iWagoUnit       = theConfiguration().GetEmgWagoUnit(iButtonIndex);
			CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->bResetAllOutputs = theConfiguration().GetEmgButtonResetAllStatus(iButtonIndex);
			CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->bRemoteControl  = theConfiguration().GetEmgButRemoteControl(iButtonIndex);

			int iButtonState = theConfiguration().GetEmgButtonState(iButtonIndex);

			if (theApp.IsServerMachine()) {
				if (iButtonState == 1) {
					CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->bButtonState = true;
					ObjTempButton->Create(strButtonText, WS_CHILD | WS_VISIBLE, ItemRect, &m_PvcsToolBar, iButtonID);
					ObjTempButton->EnableWindow(1);
				} else {
					CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->bButtonState = false;
					ObjTempButton->EnableWindow(0);
					ObjTempButton->Create(strButtonText, WS_CHILD | WS_VISIBLE, ItemRect, &m_PvcsToolBar, 00120);
				}
			} else {
				CEmgButtonOperation::m_EmgButtonInfo[iButtonIndex]->bButtonState = false;
				//ObjTempButton->EnableWindow(0);
				ObjTempButton->Create(strButtonText, WS_CHILD | WS_VISIBLE, ItemRect, &m_PvcsToolBar, 00120);
			}

			ObjTempButton->AddToolTip(strButtonToolTipText);

			ObjTempButton->UpdateToolTip(strButtonToolTipText);

			ObjTempButton->ShowWindow(SW_SHOW);

			m_PvcsToolBar.m_PvcsToolBarEmgButton.push_back(ObjTempButton);

			ItemRect.left = ItemRect.right + 2;

			ItemRect.right = ItemRect.left + 130;

			//m_PvcsToolBar.SetButtonInfo(1,ID_PUMP1,TBBS_SEPARATOR,100);
		}
	}

	// Now we create the Pump control buttons buttons 
	{
		UINT uiPumpButtonCount = CPumpButtonOperation::m_PumpButtonInfo.size();

		for (unsigned iButtonIndex = 0; iButtonIndex < uiPumpButtonCount; iButtonIndex++) {

			CString strButtonText = theConfiguration().GetPumpButtonText(iButtonIndex);
			CString strButtonToolTipText = theConfiguration().GetPumpButtonTooltip(iButtonIndex);
			CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->strButtonText   = strButtonText;
			// Get the input channels
			INT nCount = theConfiguration().GetPumpButInputCount(iButtonIndex);

			for (INT i = 0; i < nCount; i++) {
				int iConnType = theConfiguration().GetPumpButInputConnType(iButtonIndex, i );
				switch (iConnType) {
				case INP_DIGITAL : // Digital input
					{
						DigitalSignal tempDigitalSignal;
						tempDigitalSignal.Port.WagoUnit    = theConfiguration().GetPumpButWagoInputUnit(iButtonIndex,i);
						tempDigitalSignal.Port.WagoChannel = theConfiguration().GetPumpButWagoInputChNo(iButtonIndex,i);
						tempDigitalSignal.IsInverted	   = theConfiguration().GetPumpButInputInvert(iButtonIndex,i);
						tempDigitalSignal.BitNo            = -1;//theConfiguration().GetPumpInputRegBitNo(iButtonIndex, i);
						int mFunction 					   = theConfiguration().GetPumpInputFunction(iButtonIndex, i);
						CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->DigitalIn.push_back(tempDigitalSignal);
						CPumpButtonOperation::InsertInMap(CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->FunctionMap, mFunction, tempDigitalSignal);
					}
					break;
				case INP_DIG_REG:
					{
						DigitalSignal tempDigitalSignal;
						tempDigitalSignal.Port.WagoUnit    = theConfiguration().GetPumpButWagoInputUnit(iButtonIndex,i);
						tempDigitalSignal.Port.WagoChannel = theConfiguration().GetPumpButWagoInputChNo(iButtonIndex,i,&tempDigitalSignal.BitNo);
						tempDigitalSignal.IsInverted	   = theConfiguration().GetPumpButInputInvert(iButtonIndex,i);
						int mFunction 					   = theConfiguration().GetPumpInputFunction(iButtonIndex, i);
						CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->DigitalIn.push_back(tempDigitalSignal);
						CPumpButtonOperation::InsertInMap(CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->FunctionMap, mFunction, tempDigitalSignal);
					}
					break;
				case INP_ANALOG: // Analog input
					{
						AnalogSignal tempAnalogSignal;
						tempAnalogSignal.Port.WagoUnit         = theConfiguration().GetPumpButWagoInputUnit(iButtonIndex,i);
						tempAnalogSignal.Port.WagoChannel      = theConfiguration().GetPumpButWagoOutputChNo(iButtonIndex,i);
						tempAnalogSignal.Value.IsInverted	   = theConfiguration().GetPumpButInputInvert(iButtonIndex,i);
						tempAnalogSignal.Value.Limit.Threshold = theConfiguration().GetPumpButInputThreshold(iButtonIndex, i);
						CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->AnalogIn.push_back(tempAnalogSignal);
					}
					break;
				}
			} // for(i=0; i<nCount; i++)

			// Get the output channels
			nCount = theConfiguration().GetPumpButOutputCount(iButtonIndex);

			for (int i = 0; i < nCount; i++) {
				int iConnType = theConfiguration().GetPumpButOutputConnType(iButtonIndex, i );
				switch (iConnType) {
				case INP_DIGITAL:
					{
						// Digital output
						DigitalSignal tempDigitalSignal;
						tempDigitalSignal.Port.WagoUnit    = theConfiguration().GetPumpButWagoOutputUnit(iButtonIndex,i);
						tempDigitalSignal.Port.WagoChannel = theConfiguration().GetPumpButWagoOutputChNo(iButtonIndex,i);
						tempDigitalSignal.IsInverted	   = theConfiguration().GetPumpButOutputInvert(iButtonIndex,i);
						tempDigitalSignal.BitNo            = -1;//theConfiguration().GetPumpInputRegBitNo(iButtonIndex, i);
						int mFunction 					   = theConfiguration().GetPumpOutputFunction(iButtonIndex, i);
						CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->DigitalOut.push_back(tempDigitalSignal);
						CPumpButtonOperation::InsertInMap(CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->FunctionMap, mFunction, tempDigitalSignal);
						//m_uiPulseDuration.push_back( objObjectDetail.GetOutputPluse( param_iIndex, param_iSubIndex, i ) );
					}
					break;
				case INP_DIG_REG:
					{
						// Digital output
						DigitalSignal tempDigitalSignal;
						tempDigitalSignal.Port.WagoUnit    = theConfiguration().GetPumpButWagoOutputUnit(iButtonIndex,i);
						tempDigitalSignal.Port.WagoChannel = theConfiguration().GetPumpButWagoOutputChNo(iButtonIndex,i,&tempDigitalSignal.BitNo);
						tempDigitalSignal.IsInverted	   = theConfiguration().GetPumpButOutputInvert(iButtonIndex,i);
						int mFunction 					   = theConfiguration().GetPumpOutputFunction(iButtonIndex, i);
						CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->DigitalOut.push_back(tempDigitalSignal);
						CPumpButtonOperation::InsertInMap(CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->FunctionMap, mFunction, tempDigitalSignal);
						//m_uiPulseDuration.push_back( objObjectDetail.GetOutputPluse( param_iIndex, param_iSubIndex, i ) );
					}
					break;
				case INP_ANALOG:
					break;
				}
			} // for(i=0; i<nCount; i++)


			CPvcsToolBarPumpButton *ObjTempButton = new CPvcsToolBarPumpButton("PumpControl", ItemRect);
			ObjTempButton->SetPointerToButtonInfo(iButtonIndex);

			
			int iButtonState = theConfiguration().GetPumpButtonState(iButtonIndex);

			if (iButtonState == 1) {
				CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->bButtonState = true;
				// IDC_PUMPBUTTON1 IDT_PUMP1
				ObjTempButton->Create(strButtonText,WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | BS_MULTILINE, ItemRect, &m_PvcsToolBar, IDC_PUMPBUTTON1+iButtonIndex);
				ObjTempButton->SetColor(RGB(255, 255, 255), RGB(0, 147, 0), "Pump Control");
				ObjTempButton->EnableWindow(1);
			} else {
				CPumpButtonOperation::m_PumpButtonInfo[iButtonIndex]->bButtonState = false;
				ObjTempButton->Create(strButtonText, WS_CHILD | WS_VISIBLE, ItemRect, &m_PvcsToolBar, 00120);
				ObjTempButton->SetColor(RGB(255, 255, 255), RGB(0, 147, 0), "Pump Control");
				//ObjTempButton->EnableWindow(0);
			}
			m_PvcsToolBar.SetButtonInfo(iToolBarItemindex, IDT_PUMP1+1, TBBS_BUTTON, iToolBarItemindex);
			ObjTempButton->AddToolTip(strButtonToolTipText);

			ObjTempButton->UpdateToolTip(strButtonToolTipText);
			ObjTempButton->ShowWindow(SW_SHOW);

			m_PvcsToolBar.m_PvcsToolBarPumpButton.push_back(ObjTempButton);

			ItemRect.left = ItemRect.right + 2;

			ItemRect.right = ItemRect.left + 130;

		}
	}
	return 0;
}

void CPvcsFrame::OnSize(UINT nType, int cx, int cy) {
	int cxScreen = GetSystemMetrics(SM_CXSCREEN);

	if (cx == cxScreen) CFrameWnd::OnSize(nType, cx, cy);
}


void CPvcsFrame::OnNcMouseMove(UINT nHitTest, CPoint point) {
	if (nHitTest == HTMENU) {
		//AfxMessageBox("menu",1,1);
	}
	CFrameWnd::OnNcMouseMove(nHitTest, point);
}




void CPvcsFrame::OnBnClickedAlarmbutton() {
	// TODO: Add your control notification handler code here
}

void CPvcsFrame::OnBnClickedPumpButton1() {
	// TODO: Add your control notification handler code here
	CPvcsToolBarPumpButton *ObjTempButton = m_PvcsToolBar.m_PvcsToolBarPumpButton[0];
	if (ObjTempButton->ButtonConfigOK()) {
		if (ObjTempButton->HasControl()) {
			ObjTempButton->SetReleaseControl(true);
			Sleep(1000);
			ObjTempButton->SetReleaseControl(false);
		}else{
			ObjTempButton->SetControlRequest(true);
			Sleep(1000);
			ObjTempButton->SetControlRequest(false);
		}
	}else{
		int MessageResponse = MessageBox("Pump Button incorrect configured");
	}
}

void CPvcsFrame::OnBnClickedPumpButton2() {
	// TODO: Add your control notification handler code here
}

void CPvcsFrame::OnBnClickedPumpButton3() {
	// TODO: Add your control notification handler code here
}

void CPvcsFrame::OnBnClickedPumpButton4() {
	// TODO: Add your control notification handler code here
}

void CPvcsFrame::OnBnClickedPumpButton5() {
	// TODO: Add your control notification handler code here
}

