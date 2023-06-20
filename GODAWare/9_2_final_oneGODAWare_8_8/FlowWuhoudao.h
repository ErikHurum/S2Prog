#pragma once
#include "afxwin.h"


// FlowWuhoudao �Ի���

class FlowWuhoudao : public CDialog
{
	DECLARE_DYNAMIC(FlowWuhoudao)

public:
	FlowWuhoudao(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FlowWuhoudao();

	bool GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );

// �Ի�������
	enum { IDD = IDD_FLOWWUHOUDAO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
