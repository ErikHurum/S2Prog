// PvcsLodingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsLodingDialog.h"
#include "pvcsscreeninfo.h"
#include "resource.h"


// CPvcsLodingDialog dialog

IMPLEMENT_DYNAMIC(CPvcsLodingDialog, CDialog)
CPvcsLodingDialog::CPvcsLodingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPvcsLodingDialog::IDD, pParent)
{
	Create(IDD_LODING_PVCS);
	CRect rectLoadingDialog;
	GetWindowRect(&rectLoadingDialog);
	int cx = GetSystemMetrics( SM_CXSCREEN );
	int cy = GetSystemMetrics( SM_CYSCREEN );
	SetWindowPos(&CWnd::wndTopMost,(int)cx/3+30,(int)cy/6,rectLoadingDialog.Width(),rectLoadingDialog.Height(),SWP_SHOWWINDOW );    
	ShowWindow(SW_SHOW);
	UpdateWindow();
}

CPvcsLodingDialog::~CPvcsLodingDialog()
{	
	//TRACE("\nCPvcsLoadingDialog-Destuctor");
}

void CPvcsLodingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
	DDX_Control(pDX, IDC_PVCS_HANDLE, m_strScreenHandle);
	DDX_Control(pDX, IDC_LOADING_PVCS_TEXT, m_strLoading);
	DDX_Control(pDX, IDC_PVCS_PROGRESS, m_PVCSProgressCtrl);
}


BEGIN_MESSAGE_MAP(CPvcsLodingDialog, CDialog)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPvcsLodingDialog message handlers


void CPvcsLodingDialog::OnClose()
{
	//TRACE("\nEnter CPvcsLoadingDialog-OnClose");
	for(unsigned i=0;i<CPvcsScreenInfo::m_vecScreenInfo.size();i++)
	{
		delete CPvcsScreenInfo::m_vecScreenInfo[i];
	}
	//TRACE("\nLeaving CPvcsLoadingDialog-OnClose");
	delete this;
}

void CPvcsLodingDialog::ShowClosingWindow(void)
{
	CFont objFont;
	objFont.CreateFont(20,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Times New Roman");  
	m_strLoading.SetFont(&objFont);
	m_strLoading.SetWindowText("Closing PVCS...");
	m_PVCSProgressCtrl.ShowWindow(SW_HIDE);
	ShowWindow(SW_RESTORE);
	ShowWindow(SW_SHOW);
	SetTimer(1,60000,NULL);//timer keep tracks that Application must close within 60 sec., otherwise
}

void CPvcsLodingDialog::OnTimer(UINT_PTR nIDEvent)
{
	PostMessage(WM_CLOSE);
	CDialog::OnTimer(nIDEvent);
}