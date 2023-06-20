#pragma once


// FlowVxingyan dialog

class FlowVxingyan : public CDialog
{
	DECLARE_DYNAMIC(FlowVxingyan)

public:
	FlowVxingyan(CWnd* pParent = NULL);   // standard constructor
	virtual ~FlowVxingyan();

// Dialog Data
	enum { IDD = IDD_FLOWVXINGYAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006);
	double paramP1;
	double paramP;
	
	double paramB;
};
