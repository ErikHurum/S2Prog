#pragma once


// FlowJuxingbaobi dialog

class FlowJuxingbaobi : public CDialog
{
	DECLARE_DYNAMIC(FlowJuxingbaobi)

public:
	FlowJuxingbaobi(CWnd* pParent = NULL);   // standard constructor
	virtual ~FlowJuxingbaobi();

// Dialog Data
	enum { IDD = IDD_FLOWJUXINGBAOBI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006);
	double paramP1;
	double paramP;
	
	double paramB;
};
