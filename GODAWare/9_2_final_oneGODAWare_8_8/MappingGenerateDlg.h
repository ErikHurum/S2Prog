#pragma once


// CMappingGenerateDlg

class CMappingGenerateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMappingGenerateDlg)

public:
	CMappingGenerateDlg();
	virtual ~CMappingGenerateDlg();

public:
	virtual void GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray) = 0;

protected:
	virtual void OnOK(){}
	virtual void OnCancel(){}

protected:
	DECLARE_MESSAGE_MAP()
};


