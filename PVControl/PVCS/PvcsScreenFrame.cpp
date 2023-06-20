#include "StdAfx.h"
#include ".\PvcsScreenFrame.h"
#include "resource.h"
#include "PvcsObjectControlDlg.h"
#include "pvcswagocontrol.h"
#include "pvcsshipdata.h"
#include "pvcsscreeninfo.h"
#include ".\pvcs v1.0.h"
#include ".\emgbuttonoperation.h"
#include "DxfLayout.h"
#include ".\pvcscontrolobjectinfo.h"
#include "pvcscontrolobjecttimeoutinfo.h"


CWinThread *hClosingThread;
UINT RevokeThreadProc(LPVOID pParam);
UINT RequestThreadProc(LPVOID pParam);
UINT EmgButtonActionThread(LPVOID pParam);

void CloseAllSocketsThreads(void) {
	//send signal to server to take back command if any, as client going to close
	if (!theApp.IsServerMachine()) theApp.ClosingSignalOfClientToServer();

	//Send signal to close the Server/Client thread
	theApp.CloseCommandThread();
	Sleep(100);

	//if client, then send close signal to the client machine to terminate ReceiveCalibrationFile Thread
	if (!theApp.IsServerMachine()) {
		theApp.CloseReceiveCalibrationFileThread();
		Sleep(50);
	}

	if (theApp.IsServerMachine()) theApp.CloseWarningTimeoutTransferFileThread();

	return;
}

void HideWindows(void) {
	//Hide the Wago disconnect dialog
	CPvcsWagoControl::theWagoUnit().m_pdlgConnect->ShowWindow(SW_HIDE);
	if (theApp.m_pdlgManualControl) {
		theApp.m_pdlgManualControl->SendMessage(WM_CLOSE);
		delete theApp.m_pdlgManualControl;
		theApp.m_pdlgManualControl = NULL;
	}

	//hide and close wago unit status dialog box, if remains open
	if (theApp.GetWagoUnitStatusDialog() != NULL) {
		theApp.GetWagoUnitStatusDialog()->SendMessage(WM_CLOSE);
	}


	//check if Alarm List window opens
	HWND hwndAlarm = NULL;
	hwndAlarm = FindWindow(NULL, "Alarm List");

	if (hwndAlarm != NULL) ShowWindow(hwndAlarm, SW_HIDE);


	//check if Time Out List window opens
	HWND hwndTimeoutList = NULL;
	hwndTimeoutList = FindWindow(NULL, "Time Out List");

	if (hwndTimeoutList != NULL) ShowWindow(hwndTimeoutList, SW_HIDE);

	//check if calibrate window opens
	HWND hwndCalibrate = NULL;
	hwndCalibrate = FindWindow(NULL, "Calibrate");

	if (hwndCalibrate != NULL) ShowWindow(hwndCalibrate, SW_HIDE);

	//check if About Pvcs window opens
	HWND hwndAboutPvcs = NULL;
	hwndAboutPvcs = FindWindow(NULL, "About PVCS");

	if (hwndAboutPvcs != NULL) ShowWindow(hwndAboutPvcs, SW_HIDE);


	//Hide Screen Window
	for (UINT i = 0; i < CPvcsScreenInfo::m_vecScreenInfo.size(); i++) {
		CPvcsScreenInfo *CurrentScreen = (CPvcsScreenInfo *)CPvcsScreenInfo::m_vecScreenInfo[i];
		CurrentScreen->m_ptrScreenFrame->KillTimer(IDT_UPDATE_VALUES);
		CurrentScreen->m_ptrScreenFrame->ShowWindow(SW_HIDE);
	}

	theApp.GetPvcsLoadingDialog()->ShowClosingWindow();
	return;
}


//Thread to close all screen thread
UINT ClosePVCSAppThread(LPVOID pParam) {
	DWORD dExitCode;
	bool bIsThreadExited = false;
	//Sleep(500);
//	CloseHandle(CPVCSApp::ptrScreenThread->m_hThread);

	
	//TRACE("\nEnter ClosePVCSAppThread");
/*	while (!bIsThreadExited) { //check for thread exit
		::GetExitCodeThread(CPVCSApp::ptrScreenThread->m_hThread, &dExitCode);
		if (dExitCode == STILL_ACTIVE) Sleep(50);
		else {
			delete CPVCSApp::ptrScreenThread;
			bIsThreadExited = true;
		}
	}
*/
	if (theApp.m_pdlgManualControl) {
		theApp.m_pdlgManualControl->PostMessage(WM_CLOSE);
		theApp.m_pdlgManualControl->DestroyWindow();
		delete theApp.m_pdlgManualControl;
	}
	//TRACE("\nWait over");
	for (UINT i = 0; i < CPvcsScreenInfo::m_vecScreenInfo.size(); i++) {
		//TRACE("\nIn for loop of closing thread");
		if (!(CPvcsScreenInfo::m_vecScreenInfo[i]->m_bScreenClose)) {
			CPvcsScreenInfo *CurrentScreen = (CPvcsScreenInfo *)CPvcsScreenInfo::m_vecScreenInfo[i];
			//BEGINTICK("\nFrame Closing");
			bIsThreadExited = false;
			CurrentScreen->m_ptrScreenFrame->SendMessage(WM_CLOSE);
			DWORD dExitCode;
			while (!bIsThreadExited) { //check for thread exit
				::GetExitCodeThread(CPVCSApp::ptrScreenThread->m_hThread, &dExitCode);
				if (dExitCode == STILL_ACTIVE) Sleep(50);
				else {
					//delete CPVCSApp::ptrScreenThread;
					bIsThreadExited = true;
				}
			}
			//TRACE("\nWait over");
			//SHOWTICK("\nFrame_closed");
		}

	}
	//CloseHandle(m_hMutex);
	//TRACE("\nSending post message (WM_CLOSE) to CPvcsLoadingDialog");
	theApp.m_pMainWnd->PostMessage(WM_CLOSE);
	//TRACE("\nLeaving ClosePVCSAppThread");
	return 0;
}


CCriticalSection g_CS_Update;
HANDLE CPvcsScreenFrame::m_hMutex = 0;
IMPLEMENT_DYNCREATE(CPvcsScreenFrame, CPvcsFrame)

CPvcsScreenFrame::CPvcsScreenFrame(void) {
	if (!m_hMutex) {
		m_hMutex = CreateMutex(NULL, false, "ScreenFrame - Single Instance");
	}
}

CPvcsScreenFrame::~CPvcsScreenFrame(void) {
	delete m_ptrTankMap;
	if ( m_hMutex) {
		CloseHandle(m_hMutex);
		m_hMutex = 0;
	}
	//TRACE("\nCPvcsScreenFrame-Destuctor");
}

BEGIN_MESSAGE_MAP(CPvcsScreenFrame, CPvcsFrame)
ON_WM_CREATE()
ON_WM_TIMER()
ON_WM_CLOSE()
ON_UPDATE_COMMAND_UI(ID_CONTROL_COMMAND, OnUpdateControlCommand)
ON_COMMAND(ID_CONTROL_COMMAND, OnControlCommand)
ON_COMMAND_RANGE(SCREENMENUFIRSTID, SCREENMENULASTID, OnScreenSwitchMenu)
END_MESSAGE_MAP()


int CPvcsScreenFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CPvcsFrame::OnCreate(lpCreateStruct) == -1) return -1;


	return 0;
}

void CPvcsScreenFrame::OnClose() {
	//TRACE("\nEnter CPvcsScreenFrame-OnClose");
	if (theApp.IsBackupMode) {
		//if application alive, perform clean up task at once
		if (CPVCSApp::m_bIsAlive) {
			HideWindows();
			CPVCSApp::m_bIsAlive = false;
			CloseAllSocketsThreads();
			Sleep(0);
			while (!CPvcsWagoControl::theWagoUnit().WagoThreadClosed()) //exit wago read thread
				Sleep(50);
			while (!CPVCSApp::bIsShipDataThreadExit) //exit ship data thread
				Sleep(50);
			hClosingThread = AfxBeginThread(ClosePVCSAppThread, 0, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		}

		if (CPvcsScreenInfo::m_vecScreenInfo[ScreenNumber - 1]->m_bScreenClose == false) {
			CPvcsScreenInfo::m_vecScreenInfo[ScreenNumber - 1]->m_bScreenClose = true;
			//TRACE("\nCalled CPvcsFrame-OnClose");
			CPVCSApp::ptrScreenThread = CPvcsScreenInfo::m_vecScreenInfo[ScreenNumber - 1]->m_ptrScreenThread;
			CPvcsScreenInfo::m_vecScreenInfo[ScreenNumber - 1]->m_ptrScreenThread->PostThreadMessage(WM_QUIT, 0, 0);
			Sleep(100);
			CPvcsFrame::OnClose();
			hClosingThread->ResumeThread();
		}
		CPvcsWagoControl::DeleteWagoControl();

	}
	//TRACE("\nLeaving CPvcsScreenFrame-OnClose");
}

void CPvcsScreenFrame::OnTimer(UINT nIDEvent) {

	//TRACE("\nEnter CPvcsScreenFrame-OnTimer");
	// If its time to update the values
	if (nIDEvent == IDT_UPDATE_VALUES && CPVCSApp::m_bIsAlive) {
		//TRACE("\nIn Timer Code");

		if (WaitForSingleObject(CPvcsScreenFrame::m_hMutex, 3000) == WAIT_OBJECT_0) {
			//CSingleLock singlelock(&g_CS_Update);
			//singlelock.Lock();
			//if (singlelock.IsLocked()) {
			delete m_ptrTankMap;
			// then get the data
			m_ptrTankMap = theShipData().GetData();

			if (m_ptrTankMap == NULL) m_ptrTankMap = theShipData().m_DefaultTankMap;


			// Update Values in this frame
			UpdateValues();

			//singlelock.Unlock();
			/*
			for (unsigned i=0; i < CPvcsControlObjectWartsilaPump::PumpVector.size(); i++) {
				int Status = CPvcsControlObjectWartsilaPump::PumpVector[i].GetObjStatus(param_info, pSubIndex2);
			}
			*/
			ReleaseMutex(CPvcsScreenFrame::m_hMutex);
		}
	}
	//for(int i =0; i<CEmgButtonOperation::m_EmgButtonInfo.size();i++)
	//{
	//	if(CEmgButtonOperation::m_EmgButtonInfo[i]->iTotalOperation == theApp.iEmrOperationOver)
	//		::SetWindowText(m_PvcsToolBar.m_PvcsToolBarEmgButton[i]->m_hWnd,CEmgButtonOperation::m_EmgButtonInfo[i]->strButtonText);
	//}
	//CPvcsFrame::OnTimer(nIDEvent);

	//TRACE("\nLeaving CPvcsScreenFrame-OnTimer");
}

//This function is used for both Screen menu click button and for Emergncy button click
void CPvcsScreenFrame::OnScreenSwitchMenu(UINT ID) {
	//if any control window open, first close it
	if (theController().m_hWnd) ::SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);

	int ScreenNumber = ID - SCREENMENUID;

	if (ScreenNumber <= CPVCSApp::ScreenCount) { //Click on menu bar, for screen switching
		CPvcsScreenInfo::m_vecScreenInfo[ScreenNumber - 1]->m_ptrScreenFrame->ActivateFrame();
		CPvcsScreenInfo::m_vecScreenInfo[ScreenNumber - 1]->m_ptrScreenFrame->SetForegroundWindow();
	} else {
		UINT uiButtonID = ID;
		uiButtonID = ID - (SCREENMENUID + CPVCSApp::ScreenCount);
		bool ResetAllDigitalOut = CEmgButtonOperation::m_EmgButtonInfo[uiButtonID - 1]->bResetAllOutputs;
		if (ResetAllDigitalOut) {
			CPvcsWagoControl::theWagoUnit().ResetAllValues();
		} else {
			CEmgButtonOperation::ControlInfo *pControlInfo = CEmgButtonOperation::m_EmgButtonInfo[uiButtonID - 1]->Next_ControlInfo;

			//LPTSTR strTempCaption = new TCHAR[10];

			//::GetWindowText(m_PvcsToolBar.m_PvcsToolBarEmgButton[uiButtonID -1]->m_hWnd,strTempCaption,10);

			//CString strCaption = (LPCSTR)strTempCaption;

			//delete []strTempCaption;

			//if(strCaption == "Operating")
			//	return;

			//////Call SetEmgButtonOutput to set output on click on emergency button
			////CPvcsWagoControl::theWagoUnit().SetEmgButtonOutput(CEmgButtonOperation::m_EmgButtonInfo[uiButtonID - 1]->iWagoUnit,CEmgButtonOperation::m_EmgButtonInfo[uiButtonID - 1]->iWagoChNo,CEmgButtonOperation::m_EmgButtonInfo[uiButtonID - 1]->bInvertInput,true);
			//
			////::EnableWindow(m_PvcsToolBar.m_PvcsToolBarEmgButton[uiButtonID -1]->m_hWnd,FALSE);
			////::UpdateWindow(m_PvcsToolBar.m_PvcsToolBarEmgButton[uiButtonID -1]->m_hWnd);
			//::SetWindowText(m_PvcsToolBar.m_PvcsToolBarEmgButton[uiButtonID -1]->m_hWnd,"Operating");

			//Keep on while having control object for the particular button

			while (pControlInfo != NULL) {
				if (CPVCSApp::bStartNewEmgThread) {
					CWinThread *pThread = AfxBeginThread(EmgButtonActionThread, pControlInfo, THREAD_PRIORITY_HIGHEST);
					CPVCSApp::bStartNewEmgThread = false;
					pControlInfo = pControlInfo->Next_ControlInfo;
				} else Sleep(0);
			}
		}
	}

	return;
}

void CPvcsScreenFrame::OnUpdateControlCommand(CCmdUI *pCmdUI) {
	//if any control window open, first close it
	if (theController().m_hWnd) ::SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);

	if (theApp.IsServerMachine()) pCmdUI->SetText("Take Command");
	else pCmdUI->SetText("Request Command");

	//if machine not having command, then Enable its Command menu, otherwise disable it's command menu
	if (!CPvcsScreenInfo::m_vecScreenInfo[ScreenNumber - 1]->m_bCommandStatus) pCmdUI->Enable(1);
	else pCmdUI->Enable(0);
}

void CPvcsScreenFrame::OnControlCommand() {
	if (theApp.IsServerMachine()) //if server, then Revoke thread will start "Take Command"
		AfxBeginThread(RevokeThreadProc, &ScreenNumber);
	else //if not server, then request thread will start "Request Command"
		AfxBeginThread(RequestThreadProc, &ScreenNumber);

}

//Thread revoke command from the specified screen, "Take Command"
UINT RevokeThreadProc(LPVOID pParam) {
	int *RevokingScreenNumber = (int *)pParam;
	theApp.RevokingCommandFromClient(*RevokingScreenNumber);
	return 0;
}

//Thread request command from the specified screen, "Request Command"
UINT RequestThreadProc(LPVOID pParam) {
	int *RequestingScreenNumber = (int *)pParam;
	theApp.RequestingCommandFromMaster(*RequestingScreenNumber);
	return 0;
}

//Thread to carry out operation on each control for emergency button
UINT EmgButtonActionThread(LPVOID pParam) {
	CEmgButtonOperation::ControlInfo *pControlInfo;
	pControlInfo = (CEmgButtonOperation::ControlInfo *)pParam;

	CPvcsControlObjectInfo ObjCOntrolObject;
	CDxfLayout::GetControlObject(pControlInfo->uiControlIndex, pControlInfo->uiControlSubIndex, ObjCOntrolObject);

	// Set the object as not faulty
	TimeOutInfoSet::iterator it
		= theTimeOutInfo().find(CPvcsControlObjectTimeOutInfo(ObjCOntrolObject.GetIndex(), ObjCOntrolObject.GetSubIndex()));

	if (it != theTimeOutInfo().end()) ((CPvcsControlObjectTimeOutInfo)(*it)).SetTimeOut(false);

	CPVCSApp::bStartNewEmgThread = true;
	theController().GetController(ObjCOntrolObject).OnButton(ObjCOntrolObject, pControlInfo->uiActionOfButton - 1, true);

	//theApp.iEmrOperationOver++;
	return 0;
}


