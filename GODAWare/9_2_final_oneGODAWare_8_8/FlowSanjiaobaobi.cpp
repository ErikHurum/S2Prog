// FlowSanjiaobaobi.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "FlowSanjiaobaobi.h"

#include "Flow.h"
// FlowSanjiaobaobi dialog

IMPLEMENT_DYNAMIC(FlowSanjiaobaobi, CDialog)

FlowSanjiaobaobi::FlowSanjiaobaobi(CWnd* pParent /*=NULL*/)
	: CDialog(FlowSanjiaobaobi::IDD, pParent)
	, paramP(0)
	, paramP1(0)

	, paramB(0)
{

}

FlowSanjiaobaobi::~FlowSanjiaobaobi()
{
}

void FlowSanjiaobaobi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, paramP);
	DDX_Text(pDX, IDC_EDIT2, paramP1);

	DDX_Text(pDX, IDC_EDIT3, paramB);
}


BEGIN_MESSAGE_MAP(FlowSanjiaobaobi, CDialog)
END_MESSAGE_MAP()


// FlowSanjiaobaobi message handlers

bool FlowSanjiaobaobi::GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006)
{
	hightArray.RemoveAll();
	valArray.RemoveAll();


	for (int i = 0; i < 33; i++)
	{
		hightArray.Add(0.0);
		valArray.Add(0.0);
	}

	hightArray[0] = valArray[0] = 0.0;	
	for(int i = 1; i < 33; i++)
	{
		hightArray[i] = i * 0.03125*P006;
		double Q = CFlow::sanjiaobaobiyan(paramP,paramP1,paramB, hightArray[i]);
		if (Q == -999)
		{
			return false;
		}
		valArray[i] = Q;
	}
	return true;

}
