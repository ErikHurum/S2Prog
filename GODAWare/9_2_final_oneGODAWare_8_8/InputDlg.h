#pragma once
#include "afxwin.h"


// CInputDlg �Ի���

class CInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg)

public:
	CInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CInputDlg(double low, double high, CWnd* pParent = NULL);
	virtual ~CInputDlg();

// �Ի�������
	enum { IDD = IDD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
