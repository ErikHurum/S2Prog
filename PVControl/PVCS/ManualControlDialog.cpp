// ManualControlDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "ManualControlDialog.h"
#include ".\manualcontroldialog.h"


// ManualControlDialog dialog

IMPLEMENT_DYNAMIC(CManualControlDialog, CDialog)
CManualControlDialog::CManualControlDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CManualControlDialog::IDD, pParent)
{
}

CManualControlDialog::~CManualControlDialog()
{
}

void CManualControlDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BOOL CManualControlDialog::OnInitDialog() {
    //CString ver = theConfiguration().GetConfigDataVersion();
    //SetDlgItemText(IDC_EDIT,"Version: 2.6.1.1\nConfiguration File Version:" + ver +"\nCopyright: Ariston Norway\nReleased: 29 Nov 2007");
    return true;
}


BEGIN_MESSAGE_MAP(CManualControlDialog, CDialog)
		ON_WM_CLOSE()
END_MESSAGE_MAP()


// ManualControlDialog message handlers

void CManualControlDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}



void CManualControlDialog::OnClose()
{
	delete this;
}