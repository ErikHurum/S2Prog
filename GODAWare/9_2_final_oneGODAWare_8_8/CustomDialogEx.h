#pragma once


// CCustomDialogEx

class CCustomDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomDialogEx)

public:
	CCustomDialogEx();
	virtual ~CCustomDialogEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	virtual void OnCancel();
};

