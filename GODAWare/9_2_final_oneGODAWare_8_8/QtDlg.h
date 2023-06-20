#pragma once


// CQtDlg 对话框

class CQtDlg : public CDialog
{
	DECLARE_DYNAMIC(CQtDlg)

public:
	CQtDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQtDlg();

// 对话框数据
	enum { IDD = IDD_MAPPING_QT };

	void GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double R;
	double P006;
};
