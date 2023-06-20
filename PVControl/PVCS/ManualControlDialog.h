#pragma once


// ManualControlDialog dialog

class CManualControlDialog : public CDialog
{
	DECLARE_DYNAMIC(CManualControlDialog)

public:
	CManualControlDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManualControlDialog();
	virtual void OnOK();

// Dialog Data
	enum { IDD = IDD_PVCS_MANUAL_CTRL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();



	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
