// ZtDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "ZtDlg.h"
#include <math.h>

// CZtDlg 对话框

IMPLEMENT_DYNAMIC(CZtDlg, CDialog)

CZtDlg::CZtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZtDlg::IDD, pParent)
	, L(0), H(0), R(0)
{

}

CZtDlg::~CZtDlg()
{
}

void CZtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_L, L);
	DDX_Text(pDX, IDC_EDIT_H, H);
	DDX_Text(pDX, IDC_EDIT_R, R);
}

void CZtDlg::GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 )
{
	const double PI = 3.1415926535897932384626434;

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
		hightArray[i] = (float)(i * 0.03125*P006);
		if(hightArray[i] < H )
		{
			valArray[i] = (float)(1/3.0*PI*pow(R,2.0)*hightArray[i]);
		}
		else
		{
			valArray[i] = (float)(1/3.0*PI*pow(R,2.0)*H + PI*pow(R,2.0)*(hightArray[i] - H));
		}
	}	
}


BEGIN_MESSAGE_MAP(CZtDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CZtDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CZtDlg 消息处理程序

void CZtDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (H < P006)
	{
		WarnMessageBox(IDS_MAPPINGWARN1);
		return;
	}
	OnOK();
}
