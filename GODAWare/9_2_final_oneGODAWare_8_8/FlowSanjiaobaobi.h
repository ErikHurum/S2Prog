#pragma once


// FlowSanjiaobaobi dialog

class FlowSanjiaobaobi : public CDialog
{
	DECLARE_DYNAMIC(FlowSanjiaobaobi)

public:
	FlowSanjiaobaobi(CWnd* pParent = NULL);   // standard constructor
	virtual ~FlowSanjiaobaobi();

// Dialog Data
	enum { IDD = IDD_FLOWSANJIAOBAOBI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double paramP;
	double paramP1;

	bool GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006);
	double paramB;
};
