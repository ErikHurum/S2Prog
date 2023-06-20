// WagoUnitStatus.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "WagoUnitStatus.h"
#include "pvcswagocontrol.h"
#include ".\wagounitstatus.h"

// CWagoUnitStatus dialog

IMPLEMENT_DYNAMIC(CWagoUnitStatus, CDialog)
CWagoUnitStatus::CWagoUnitStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CWagoUnitStatus::IDD, pParent)
{
	Create(IDD_WagoUnitStatus);
	CRect rectWagoUnitDialog;
	GetWindowRect(&rectWagoUnitDialog);
	int cx = GetSystemMetrics( SM_CXSCREEN );
	int cy = GetSystemMetrics( SM_CYSCREEN );
	SetWindowPos(&CWnd::wndTop,(int)cx/3+25,(int)cy/6+180,rectWagoUnitDialog.Width(),rectWagoUnitDialog.Height(),SWP_FRAMECHANGED);    
	ShowWindow(SW_SHOW);
	UpdateWindow();
}

CWagoUnitStatus::~CWagoUnitStatus()
{
}

void CWagoUnitStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WagoUnitStatusList, m_WagoUnitStatusList);
}


BEGIN_MESSAGE_MAP(CWagoUnitStatus, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDWagoUnitStatusOK, OnBnClickedWagounitstatusok)
	ON_WM_CLOSE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_WagoUnitStatusList, OnLvnItemchangedWagounitstatuslist)
END_MESSAGE_MAP()


// CWagoUnitStatus message handlers

BOOL CWagoUnitStatus::OnInitDialog()
{
	CDialog::OnInitDialog();
	BuildGrid();
	FillGrid();
	SetTimer(1,5000,NULL);
	return true;
}

//build grid
void CWagoUnitStatus::BuildGrid(void)
{
	m_WagoUnitStatusList.SetExtendedStyle( m_WagoUnitStatusList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );
	
	m_WagoUnitStatusList.InsertColumn(0,"S.No.");
	m_WagoUnitStatusList.InsertColumn(1,"Wago Unit Connection Status");
	m_WagoUnitStatusList.InsertColumn(2,"Wago Unit IP");

	m_WagoUnitStatusList.SetColumnWidth(0,50);
	m_WagoUnitStatusList.SetColumnWidth(1,170);
	m_WagoUnitStatusList.SetColumnWidth(2,100);

}

//fill grid with data
void CWagoUnitStatus::FillGrid(void)
{
	//Remove all old entries from the list
	m_WagoUnitStatusList.DeleteAllItems();

	CString strTemp;
	for(unsigned i = 0; i<CPvcsWagoControl::theWagoUnit().theWagoStatus.size();i++)
	{
		strTemp.Format("%d",i);
		
		//S.No.
		m_WagoUnitStatusList.InsertItem(i,strTemp);

		//Wago Unit Connection Status
		if(CPvcsWagoControl::theWagoUnit().theWagoStatus[i]->WagoConnectionStatus )
			strTemp.Format("Not Connected");
		else
			strTemp.Format("Connected");

		m_WagoUnitStatusList.SetItemText(i,1,strTemp);
				
		//Wago Unit First IP
		m_WagoUnitStatusList.SetItemText(i,2,CPvcsWagoControl::theWagoUnit().theWagoStatus[i]->WagoIP);

	}
}

void CWagoUnitStatus::OnTimer(UINT_PTR nIDEvent)
{
	//FillGrid();
	CString strTemp;
	for(unsigned i = 0; i<CPvcsWagoControl::theWagoUnit().theWagoStatus.size();i++)
	{
		//Wago Unit Connection Status
		if(CPvcsWagoControl::theWagoUnit().theWagoStatus[i]->WagoConnectionStatus )
			strTemp.Format("Not Connected");
		else
			strTemp.Format("Connected");

		m_WagoUnitStatusList.SetItemText(i,1,strTemp);
				
	}

	CDialog::OnTimer(nIDEvent);
}

void CWagoUnitStatus::OnBnClickedWagounitstatusok()
{
	delete theApp.GetWagoUnitStatusDialog();
	theApp.SetNULLWagoUnitStatusDialog();
}

void CWagoUnitStatus::OnClose()
{
	delete theApp.GetWagoUnitStatusDialog();
	theApp.SetNULLWagoUnitStatusDialog();
}
void CWagoUnitStatus::OnLvnItemchangedWagounitstatuslist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
