#pragma once


// CSpytDlg 对话框

class CSpytDlg : public CDialog
{
	DECLARE_DYNAMIC(CSpytDlg)

public:
	CSpytDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSpytDlg();

// 对话框数据
	enum { IDD = IDD_MAPPING_SPYT };

	void GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double L;
	double H;
	double D;


	double P006;
};
