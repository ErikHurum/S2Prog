
#pragma once
#include "resource.h"

// CPvcsWagoConnectDlg dialog

class CPvcsWagoConnectDlg : public CDialog
{
	DECLARE_DYNAMIC(CPvcsWagoConnectDlg)

public:
	CPvcsWagoConnectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual void OnOK();
	virtual ~CPvcsWagoConnectDlg();

// Dialog Data
	enum { IDD = IDD_PVCSWAGOCONNECTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
