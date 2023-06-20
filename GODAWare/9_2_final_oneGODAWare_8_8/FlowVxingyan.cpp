// FlowVxingyan.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "FlowVxingyan.h"
#include "Flow.h"


// FlowVxingyan dialog

IMPLEMENT_DYNAMIC(FlowVxingyan, CDialog)

FlowVxingyan::FlowVxingyan(CWnd* pParent /*=NULL*/)
	: CDialog(FlowVxingyan::IDD, pParent)
	, paramP1(0)
	, paramP(0)
	
	, paramB(0)
{

}

FlowVxingyan::~FlowVxingyan()
{
}

void FlowVxingyan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, paramP1);
	DDX_Text(pDX, IDC_EDIT1, paramP);

	DDX_Text(pDX, IDC_EDIT3, paramB);
}


BEGIN_MESSAGE_MAP(FlowVxingyan, CDialog)
END_MESSAGE_MAP()


// FlowVxingyan message handlers

bool FlowVxingyan::GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006)
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
		double Q = CFlow::Vxingyan(paramP,paramP1,paramB, hightArray[i]);
		if (Q == -999)
		{
			return false;
		}
		valArray[i] = Q;
	}
	return true;
}
