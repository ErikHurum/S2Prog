// FlowDengkuanbaobi.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "FlowDengkuanbaobi.h"
#include "Flow.h"

// FlowDengkuanbaobi dialog

IMPLEMENT_DYNAMIC(FlowDengkuanbaobi, CDialog)

FlowDengkuanbaobi::FlowDengkuanbaobi(CWnd* pParent /*=NULL*/)
	: CDialog(FlowDengkuanbaobi::IDD, pParent)	
{
	paramP=0.0;
	paramB=0.0;
}

FlowDengkuanbaobi::~FlowDengkuanbaobi()
{
}

void FlowDengkuanbaobi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, paramP);
	DDX_Text(pDX, IDC_EDIT2, paramB);
}


BEGIN_MESSAGE_MAP(FlowDengkuanbaobi, CDialog)
END_MESSAGE_MAP()


// FlowDengkuanbaobi message handlers

bool FlowDengkuanbaobi::GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006 )
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
		double Q = CFlow::dengkuanbaobiyan(paramP,paramB, hightArray[i]);
		if (Q == -999)
		{
			return false;
		}
		valArray[i] = Q;
	}
	return true;
}
