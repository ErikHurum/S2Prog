#pragma once


// CSpytDlg �Ի���

class CSpytDlg : public CDialog
{
	DECLARE_DYNAMIC(CSpytDlg)

public:
	CSpytDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSpytDlg();

// �Ի�������
	enum { IDD = IDD_MAPPING_SPYT };

	void GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double L;
	double H;
	double D;


	double P006;
};
