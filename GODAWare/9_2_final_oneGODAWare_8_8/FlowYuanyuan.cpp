// FlowYuanyuan.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "FlowYuanyuan.h"
#include "Flow.h"

// FlowYuanyuan dialog

IMPLEMENT_DYNAMIC(FlowYuanyuan, CDialog)

FlowYuanyuan::FlowYuanyuan(CWnd* pParent /*=NULL*/)
	: CDialog(FlowYuanyuan::IDD, pParent)
	, paramP1(0)
	, paramP(0)

	, paramB(0)
	, paramL(0)
{

}

FlowYuanyuan::~FlowYuanyuan()
{
}

void FlowYuanyuan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT68, paramP1);
	DDX_Text(pDX, IDC_EDIT1, paramP);

	DDX_Text(pDX, IDC_EDIT2, paramB);
	DDX_Text(pDX, IDC_EDIT3, paramL);
}


BEGIN_MESSAGE_MAP(FlowYuanyuan, CDialog)
END_MESSAGE_MAP()


// FlowYuanyuan message handlers

bool FlowYuanyuan::GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006 )
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
		double Q = CFlow::yuanyuan(paramP,paramP1,paramB,paramL, hightArray[i]);
		if (Q == -999)
		{
			return false;
		}
		valArray[i] = Q;
	}
	return true;
}
