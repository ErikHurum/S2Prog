// PvcsPasswordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsPasswordDialog.h"
#include ".\pvcsconfiguration.h"


int PvcsPasswordDialog::m_dialoginitalise=0;
bool PvcsPasswordDialog::DialgVisible=false;

// PvcsPasswordDialog dialog

IMPLEMENT_DYNAMIC(PvcsPasswordDialog, CDialogEx)

PvcsPasswordDialog::PvcsPasswordDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(PvcsPasswordDialog::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	    // Inialize memory DC for double buffering
    m_hMemDC = CreateCompatibleDC(NULL);
	Password = theConfiguration().GetPassword();
}

PvcsPasswordDialog::~PvcsPasswordDialog()
{
}

void PvcsPasswordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PvcsPasswordDialog, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &PvcsPasswordDialog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT2, &PvcsPasswordDialog::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &PvcsPasswordDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// PvcsPasswordDialog message handlers


void PvcsPasswordDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void PvcsPasswordDialog::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	/*
	CString s;
	GetDlgItemText(IDC_EDIT2, s);
	if ( Password == s ) CDialogEx::OnOK();
	*/
}


const CPvcsControlObjectInfo& PvcsPasswordDialog::GetControlobjectInfo(void) {
    return m_infoObject;
}


// Function name   : theController
// Description     : Access function for one and only Controller Dialog
// Return type     : CPvcsControlObjectDlg&

PvcsPasswordDialog& thePasswordMessage() {
    static PvcsPasswordDialog dlgControl;
    return dlgControl;
}


void PvcsPasswordDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString s;
	GetDlgItemText(IDC_EDIT2, s);
	if ( Password == s ){
		CDialogEx::OnOK();
	}else{
		CDialogEx::OnCancel();
	}
}
