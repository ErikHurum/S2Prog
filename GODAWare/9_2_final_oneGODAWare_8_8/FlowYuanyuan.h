#pragma once


// FlowYuanyuan dialog

class FlowYuanyuan : public CDialog
{
	DECLARE_DYNAMIC(FlowYuanyuan)

public:
	FlowYuanyuan(CWnd* pParent = NULL);   // standard constructor
	virtual ~FlowYuanyuan();

// Dialog Data
	enum { IDD = IDD_FLOWYUANYUAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006 );
	double paramP1;
	double paramP;

	double paramB;
	double paramL;
};
