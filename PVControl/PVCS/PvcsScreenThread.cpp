// ScreenThread.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "pvcsScreenThread.h"
#include "PvcsScreenFrame.h"
#include "PvcsScreenInfo.h"
#include "pvcsconfiguration.h"

// CPvcsScreenThread

IMPLEMENT_DYNCREATE(CPvcsScreenThread, CWinThread)

CPvcsScreenThread::CPvcsScreenThread()
{
	ResetEvent(CPVCSApp::hEvent_ScreenThread);
	//TRACE("%d Thread Started\n",CPVCSApp::ScreenIndex);
}

CPvcsScreenThread::~CPvcsScreenThread()
{
	//TRACE("\nCPvcsScreenThread-Destructor");
}

BOOL CPvcsScreenThread::InitInstance()
{
	// Install the Win32 Exception Handler
	CWin32Exception::install_handler();

	// Create a frame
	CPvcsScreenFrame * pFrame = new CPvcsScreenFrame();
	
	if (!pFrame)//if not created then return false
	{
		SetEvent(CPVCSApp::hEvent_ScreenThread);
		return FALSE;
	}

	CString ScreenTitle = "", TempTitle = "";

    pFrame->ScreenNumber = CPVCSApp::ScreenIndex;
	CPvcsScreenInfo *pScreenInfo = new CPvcsScreenInfo();
	
	if(theApp.IsServerMachine())
		pScreenInfo->m_bCommandStatus = true;
	else
		pScreenInfo->m_bCommandStatus = false;

	pScreenInfo->m_strCommandingMachineIP = theApp.GetMasterIP();
	pScreenInfo->m_ptrScreenFrame = pFrame;
	pScreenInfo->m_ptrScreenThread = this; 
	
	CPvcsScreenInfo::m_vecScreenInfo.push_back(pScreenInfo);

	this->m_pMainWnd = pFrame;

	//set window title
	pScreenInfo->m_strScreenTitle = theConfiguration().GetScreenTitle(pFrame->ScreenNumber);
	TempTitle = pScreenInfo->m_strScreenTitle;

	if(theApp.IsBackupMode )//if in backup mode
	{
		ScreenTitle.Format("PVCS Backup - %s,",TempTitle);
	}
	else
	{
		ScreenTitle.Format("PVCS - %s,",TempTitle);
	}
	
	if(theApp.IsServerMachine())//if server
		TempTitle.Format("%s Master",ScreenTitle);
	else
		TempTitle.Format("%s Client",ScreenTitle);

	if(pScreenInfo->m_bCommandStatus)//if command
		ScreenTitle.Format("%s in Command Mode",TempTitle);
	else
		ScreenTitle.Format("%s in Display Mode",TempTitle);

	
	pFrame->LoadFrame(IDR_MAINFRAME);
	
	pFrame->SetWindowText(ScreenTitle);

	//TRACE("%d Thread End\n",CPVCSApp::ScreenIndex);
	SetEvent(CPVCSApp::hEvent_ScreenThread);
	return TRUE;
	
}

int CPvcsScreenThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	//SetEvent(CPVCSApp::hEvent_CloseScreenThread);
	//TRACE("\nCPvcsScreenThread-ExitInstance");
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPvcsScreenThread, CWinThread)
END_MESSAGE_MAP()


// CPvcsScreenThread message handlers
