#pragma once


// CZtDlg 对话框

class CZtDlg : public CDialog
{
	DECLARE_DYNAMIC(CZtDlg)

public:
	CZtDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZtDlg();

// 对话框数据
	enum { IDD = IDD_MAPPING_ZT };

	void GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double L,H,R;
	double P006;
};
