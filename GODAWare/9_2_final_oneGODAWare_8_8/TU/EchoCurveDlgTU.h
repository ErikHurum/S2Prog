#pragma once
#include "../resource.h"
#include "afxwin.h"
#include "../CurveDialog.h"

// CEchoCurveDlgTU

class CEchoCurveDlgTU : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CEchoCurveDlgTU)

public:
	CEchoCurveDlgTU();
	virtual ~CEchoCurveDlgTU();


	enum {IDD = IDD_ECHOCURVE_TU};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

	void UncompressData( const CArray<BYTE>& byteArray , vector<curvevalue>& curveValueVec, double xScale, double maxXvalue = 0);

	
public:
	CButton m_echoCurve;
	CButton m_envelop;
	CButton m_falseEcho;

	afx_msg void OnBnClickedBtnLoad();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);


private:
	vector<curvevalue> m_echoCurveVec;
	vector<curvevalue> m_envelopVec;
	vector<curvevalue> m_falseEchoVec;
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CCurveDialog m_curveDraw;
	afx_msg void OnPaint();
};


