// PvcsWagoConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsWagoConnectDlg.h"
#include ".\pvcswagoconnectdlg.h"


// CPvcsWagoConnectDlg dialog

IMPLEMENT_DYNAMIC(CPvcsWagoConnectDlg, CDialog)
CPvcsWagoConnectDlg::CPvcsWagoConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPvcsWagoConnectDlg::IDD, pParent)
{
}

CPvcsWagoConnectDlg::~CPvcsWagoConnectDlg()
{
}

void CPvcsWagoConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPvcsWagoConnectDlg, CDialog)
END_MESSAGE_MAP()


// CPvcsWagoConnectDlg message handlers

void CPvcsWagoConnectDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

