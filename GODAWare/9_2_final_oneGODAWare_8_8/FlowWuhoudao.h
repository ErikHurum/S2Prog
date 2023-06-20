#pragma once
#include "afxwin.h"


// FlowWuhoudao 对话框

class FlowWuhoudao : public CDialog
{
	DECLARE_DYNAMIC(FlowWuhoudao)

public:
	FlowWuhoudao(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FlowWuhoudao();

	bool GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );

// 对话框数据
	enum { IDD = IDD_FLOWWUHOUDAO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();

private:
	int b;
public:
	CComboBox m_combo_b;
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboB();
	afx_msg void OnBnClickedCancel();
};
