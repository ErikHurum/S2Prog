// FlowSanjiaopoumian.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "FlowSanjiaopoumian.h"
#include "Flow.h"

// FlowSanjiaopoumian dialog

IMPLEMENT_DYNAMIC(FlowSanjiaopoumian, CDialog)

FlowSanjiaopoumian::FlowSanjiaopoumian(CWnd* pParent /*=NULL*/)
	: CDialog(FlowSanjiaopoumian::IDD, pParent)
	, paramP(0)
	
	, paramB(0)
{

}

FlowSanjiaopoumian::~FlowSanjiaopoumian()
{
}

void FlowSanjiaopoumian::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, paramP);

	DDX_Text(pDX, IDC_EDIT2, paramB);
}


BEGIN_MESSAGE_MAP(FlowSanjiaopoumian, CDialog)
END_MESSAGE_MAP()


// FlowSanjiaopoumian message handlers

bool FlowSanjiaopoumian::GenerateMapping(CArray<double>& hightArray, CArray<double>& valArray, double P006 )
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
		double Q = CFlow::sanjiaoxingpoumianyan(paramP,paramB, hightArray[i]);
		if (Q == -999)
		{
			return false;
		}
		valArray[i] = Q;
	}
	return true;

}
