// FlowJuxingkuanding.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "FlowJuxingkuanding.h"
#include "Flow.h"

// FlowJuxingkuanding dialog

IMPLEMENT_DYNAMIC(FlowJuxingkuanding, CDialog)

FlowJuxingkuanding::FlowJuxingkuanding(CWnd* pParent /*=NULL*/)
	: CDialog(FlowJuxingkuanding::IDD, pParent)
	, paramP(0)
	
	, paramB(0)
	, paramL(0)
{

}

FlowJuxingkuanding::~FlowJuxingkuanding()
{
}

void FlowJuxingkuanding::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, paramP);

	DDX_Text(pDX, IDC_EDIT2, paramB);
	DDX_Text(pDX, IDC_EDIT3, paramL);
}


BEGIN_MESSAGE_MAP(FlowJuxingkuanding, CDialog)
END_MESSAGE_MAP()


// FlowJuxingkuanding message handlers

bool FlowJuxingkuanding::GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006)
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
		double Q = CFlow::juxingkuandingyan(paramP,paramB,paramL, hightArray[i]);
		if (Q == -999)
		{
			return false;
		}
		valArray[i] = Q;
	}
	return true;
}
