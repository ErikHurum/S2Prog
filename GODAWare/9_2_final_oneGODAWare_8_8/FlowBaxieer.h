#pragma once
#include "afxwin.h"


// FlowBaxieer �Ի���

class FlowBaxieer : public CDialog
{
	DECLARE_DYNAMIC(FlowBaxieer)

public:
	FlowBaxieer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FlowBaxieer();

	bool GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );

// �Ի�������
	enum { IDD = IDD_FLOWBAXIEER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo_b;
private:
	int p981;
protected:
	virtual void OnOK();
};
