#pragma once


// FlowJuxingkuanding dialog

class FlowJuxingkuanding : public CDialog
{
	DECLARE_DYNAMIC(FlowJuxingkuanding)

public:
	FlowJuxingkuanding(CWnd* pParent = NULL);   // standard constructor
	virtual ~FlowJuxingkuanding();

// Dialog Data
	enum { IDD = IDD_FLOWJUXINGKUANDING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006);
	double paramP;

	double paramB;
	double paramL;
};
