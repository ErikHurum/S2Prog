#pragma once
#include "afxwin.h"


// FlowBaxieer 对话框

class FlowBaxieer : public CDialog
{
	DECLARE_DYNAMIC(FlowBaxieer)

public:
	FlowBaxieer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FlowBaxieer();

	bool GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 );

// 对话框数据
	enum { IDD = IDD_FLOWBAXIEER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo_b;
private:
	int p981;
protected:
	virtual void OnOK();
};
