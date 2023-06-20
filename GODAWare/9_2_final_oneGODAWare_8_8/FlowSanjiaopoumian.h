#pragma once


// FlowSanjiaopoumian dialog

class FlowSanjiaopoumian : public CDialog
{
	DECLARE_DYNAMIC(FlowSanjiaopoumian)

public:
	FlowSanjiaopoumian(CWnd* pParent = NULL);   // standard constructor
	virtual ~FlowSanjiaopoumian();

// Dialog Data
	enum { IDD = IDD_FLOWSANJIAOPOUMIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006 );
	double paramP;

	double paramB;
};
