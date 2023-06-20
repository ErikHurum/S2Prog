#pragma once


// FlowDengkuanbaobi dialog

class FlowDengkuanbaobi : public CDialog
{
	DECLARE_DYNAMIC(FlowDengkuanbaobi)

public:
	FlowDengkuanbaobi(CWnd* pParent = NULL);   // standard constructor
	virtual ~FlowDengkuanbaobi();

// Dialog Data
	enum { IDD = IDD_FLOWDENGKUANBAOBI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006 );
	double paramP;
	
	double paramB;
};
