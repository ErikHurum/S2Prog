#pragma once
#include "afxwin.h"
#include "MappingGenerateDlg.h"


class CMappingEditDlg: public CDialogEx
{
	DECLARE_DYNAMIC(CMappingEditDlg)

public:
	CMappingEditDlg(CWnd* pParent = NULL, int pn = 0 );

	enum {IDD = IDD_MAPPINGEDIT};

	void SaveData();
	void LoadData();

protected:
	float m_hightRatio, m_valRatio;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnLoad();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_hight[33];
	CEdit m_mapVal[33];
//	virtual BOOL OnInitDialog();
	CComboBox m_unit;
	CComboBox m_mapType;
	CComboBox m_vesselType;

	afx_msg void OnCbnSelchangeComboLintype();
	afx_msg void OnBnClickedBtnSave();

	afx_msg void OnBnClickedButtonResetval();
	afx_msg void OnBnClickedBtnReadfilie();
	afx_msg void OnBnClickedBtnSavefile();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButtonGenerate();
//	virtual BOOL OnInitDialog();
private:

	float lowPercent, low, highPercent, high, val0, val100;
	CArray<double> hightArray, valArray;
	int pointnumber;

	void DisplayValue(CArray<float>&val);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CEdit m_editDensity;
	afx_msg void OnCbnSelchangeComboVesseltype();
	CComboBox m_comboFlowType;
	afx_msg void OnCbnSelchangeComboUnit();
};


