#pragma once


// CQtDlg �Ի���

class CQtDlg : public CDialog
{
	DECLARE_DYNAMIC(CQtDlg)

public:
	CQtDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQtDlg();

// �Ի�������
	enum { IDD = IDD_MAPPING_QT };

	void GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double R;
	double P006;
};
