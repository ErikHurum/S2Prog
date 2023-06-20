// SpytDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "SpytDlg.h"
#include <math.h>

// CSpytDlg 对话框

IMPLEMENT_DYNAMIC(CSpytDlg, CDialog)

CSpytDlg::CSpytDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpytDlg::IDD, pParent)
	, L(0)
	, H(0)
	, D(0)
	, P006(0)
{

}

CSpytDlg::~CSpytDlg()
{
}

void CSpytDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_L, L);
	DDX_Text(pDX, IDC_EDIT_H, H);
	DDX_Text(pDX, IDC_EDIT_D, D);
}

void CSpytDlg::GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 )
{
	const double PI = 3.1415926535897932384626434;

	hightArray.RemoveAll();
	valArray.RemoveAll();


	for (int i = 0; i < 33; i++)
	{
		hightArray.Add(0.0);
		valArray.Add(0.0);
	}


	//if(H/2>=P006)
	//{
	//	V=PI*pow(H/2,2)*L;
	//	V=acos((H/2-P006)/(H/2))/PI*V;
	//	V=V-(H/2-P006)*sqrt(H*P006-pow(P006,2))*L;
	//}
	//else
	//{
	//	V=PI*pow(H/2,2)*L;
	//	V=(PI-acos((P006-H/2)/(H/2)))/PI*V;
	//	V=V+(P006-H/2)*sqrt(pow(H/2,2)-pow((P006-H/2),2))*L;
	//}

	hightArray[0] = valArray[0] = 0.0;	
	for(int i = 1; i < 33; i++)
	{
		hightArray[i] = (float)(i * 0.03125*P006);
		if(hightArray[i]<=H/2)
		{
			valArray[i]=PI*pow(H/2,2)*L;
			valArray[i]=acos((H/2-hightArray[i])/(H/2))/PI*valArray[i];
			valArray[i]=valArray[i]-(H/2-hightArray[i])*sqrt(H*hightArray[i]-pow(hightArray[i],2))*L;
		}
		else
		{
			valArray[i]=PI*pow(H/2,2)*L;
			valArray[i]=(PI-acos((hightArray[i]-H/2)/(H/2)))/PI*valArray[i];
			valArray[i]=valArray[i]+(hightArray[i]-H/2)*sqrt(pow(H/2,2)-pow((hightArray[i]-H/2),2))*L;
		}
	}	
}


BEGIN_MESSAGE_MAP(CSpytDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSpytDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSpytDlg 消息处理程序

void CSpytDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (H < P006)
	{
		WarnMessageBox(IDS_MAPPINGWARN1);
		return;
	}
	OnOK();
}
