#pragma once


// CZtDlg �Ի���

class CZtDlg : public CDialog
{
	DECLARE_DYNAMIC(CZtDlg)

public:
	CZtDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZtDlg();

// �Ի�������
	enum { IDD = IDD_MAPPING_ZT };

	void GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double L,H,R;
	double P006;
};
