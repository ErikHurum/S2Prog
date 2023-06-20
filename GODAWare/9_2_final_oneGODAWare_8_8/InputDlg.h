#pragma once
#include "afxwin.h"


// CInputDlg 对话框

class CInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg)

public:
	CInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	CInputDlg(double low, double high, CWnd* pParent = NULL);
	virtual ~CInputDlg();

// 对话框数据
	enum { IDD = IDD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_label;
	CEdit m_value;
	afx_msg void OnBnClickedOk();

	const CString& GetString() const {return m_strValue;}
	double GetDouble() const {return m_dbValue;}

	void SetLabel(const CString& s) {m_labelText = s;}

private:
	CString m_strValue;
	CString m_labelText;
	double m_dbValue;
	double m_low;
	double m_high;
	bool m_range;
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
