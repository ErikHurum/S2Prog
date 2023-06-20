#pragma once
#include "afxwin.h"
#include "OperationDlg.h"

// CInfoDlg

class CInfoDlg : public COperationDlg
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg();
	virtual ~CInfoDlg();

	enum { IDD = IDD_INFO};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

	void LoadData();
	void SaveData();

	CString lastDeviceType;
	CString lastSerialNum;
	CString lastDate;

};


