#pragma once
#include "afxwin.h"


// CCalibrationDlg

class CCalibrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalibrationDlg)

public:
	CCalibrationDlg(CWnd* pParent = NULL);


	enum {IDD = IDD_CALIBRATION};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:

	int validPoint;

	CEdit m_editMeasuredVal[33];
	CEdit m_editCaliVal[33];

	float m_measuredVal[33];
	float m_caliVal[33];
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
	virtual BOOL OnInitDialog();
};


