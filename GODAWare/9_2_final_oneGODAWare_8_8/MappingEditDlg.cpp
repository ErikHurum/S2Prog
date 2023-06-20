// MappingEditDlgPR.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "MappingEditDlg.h"
#include "SpytDlg.h"
#include "QtDlg.h"
#include "ZtDlg.h"

#include "FlowBaxieer.h"
#include "FlowWuhoudao.h"
#include "FlowDengkuanbaobi.h"
#include "FlowJuxingbaobi.h"
#include "FlowJuxingkuanding.h"
#include "FlowSanjiaobaobi.h"
#include "FlowSanjiaopoumian.h"
#include "FlowVxingyan.h"
#include "FlowYuanyuan.h"
// CMappingEditDlg

IMPLEMENT_DYNAMIC(CMappingEditDlg, CDialogEx)

CMappingEditDlg::CMappingEditDlg(CWnd* pParent, int pn)
: CDialogEx(IDD_MAPPINGEDIT, pParent), pointnumber(pn)
{

}


BEGIN_MESSAGE_MAP(CMappingEditDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMappingEditDlg::OnBnClickedBtnLoad)
	ON_CBN_SELCHANGE(IDC_COMBO_LINTYPE, &CMappingEditDlg::OnCbnSelchangeComboLintype)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMappingEditDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BUTTON_RESETVAL, &CMappingEditDlg::OnBnClickedButtonResetval)
	ON_BN_CLICKED(IDC_BTN_READFILIE, &CMappingEditDlg::OnBnClickedBtnReadfilie)
	ON_BN_CLICKED(IDC_BTN_SAVEFILE, &CMappingEditDlg::OnBnClickedBtnSavefile)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CMappingEditDlg::OnBnClickedButtonGenerate)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_VESSELTYPE, &CMappingEditDlg::OnCbnSelchangeComboVesseltype)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT, &CMappingEditDlg::OnCbnSelchangeComboUnit)
END_MESSAGE_MAP()



// CMappingEditDlg 消息处理程序



void CMappingEditDlg::OnBnClickedBtnLoad()
{
	CProgress progress;
	CString str;
	CArray<float> arrayData;

	UINT8 intData;
	

	while(!(theApp.m_pClient->LoadData(0x110, lowPercent, pointnumber)));
	while(!(theApp.m_pClient->LoadData(0x111, low, pointnumber)));
	while(!(theApp.m_pClient->LoadData(0x112, highPercent, pointnumber)));
	while(!(theApp.m_pClient->LoadData(0x113, high, pointnumber)));


	theApp.m_pClient->LoadData(0x114, val0, pointnumber);
	theApp.m_pClient->LoadData(0x115, val100, pointnumber);

	m_hightRatio = (low - high) / (highPercent - lowPercent);
	m_valRatio = val100 - val0;

	theApp.m_pClient->LoadData(0x12, intData, pointnumber);
	m_mapType.SetCurSel(intData -  1);
	OnCbnSelchangeComboLintype();

	theApp.m_pClient->LoadData(0x13, intData, pointnumber);
	m_unit.SetCurSel(intData - 1);

	theApp.m_pClient->LoadData(0x10, intData, pointnumber);
	m_vesselType.SetCurSel(intData -  2);
	OnCbnSelchangeComboVesseltype();


	theApp.m_pClient->LoadData(0x994, arrayData, pointnumber);
	if(arrayData.GetSize() == 66)
	{
		DisplayValue(arrayData);
	}
}

void CMappingEditDlg::DoDataExchange(CDataExchange* pDX)
{


	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HIGHT0, m_hight[0]);
	DDX_Control(pDX, IDC_EDIT_HIGHT1, m_hight[1]);
	DDX_Control(pDX, IDC_EDIT_HIGHT2, m_hight[2]);
	DDX_Control(pDX, IDC_EDIT_HIGHT3, m_hight[3]);
	DDX_Control(pDX, IDC_EDIT_HIGHT4, m_hight[4]);
	DDX_Control(pDX, IDC_EDIT_HIGHT5, m_hight[5]);
	DDX_Control(pDX, IDC_EDIT_HIGHT6, m_hight[6]);
	DDX_Control(pDX, IDC_EDIT_HIGHT7, m_hight[7]);
	DDX_Control(pDX, IDC_EDIT_HIGHT8, m_hight[8]);
	DDX_Control(pDX, IDC_EDIT_HIGHT9, m_hight[9]);
	DDX_Control(pDX, IDC_EDIT_HIGHT10, m_hight[10]);
	DDX_Control(pDX, IDC_EDIT_HIGHT11, m_hight[11]);
	DDX_Control(pDX, IDC_EDIT_HIGHT12, m_hight[12]);
	DDX_Control(pDX, IDC_EDIT_HIGHT13, m_hight[13]);
	DDX_Control(pDX, IDC_EDIT_HIGHT14, m_hight[14]);
	DDX_Control(pDX, IDC_EDIT_HIGHT15, m_hight[15]);
	DDX_Control(pDX, IDC_EDIT_HIGHT16, m_hight[16]);
	DDX_Control(pDX, IDC_EDIT_HIGHT17, m_hight[17]);
	DDX_Control(pDX, IDC_EDIT_HIGHT18, m_hight[18]);
	DDX_Control(pDX, IDC_EDIT_HIGHT19, m_hight[19]);
	DDX_Control(pDX, IDC_EDIT_HIGHT20, m_hight[20]);
	DDX_Control(pDX, IDC_EDIT_HIGHT21, m_hight[21]);
	DDX_Control(pDX, IDC_EDIT_HIGHT22, m_hight[22]);
	DDX_Control(pDX, IDC_EDIT_HIGHT23, m_hight[23]);
	DDX_Control(pDX, IDC_EDIT_HIGHT24, m_hight[24]);
	DDX_Control(pDX, IDC_EDIT_HIGHT25, m_hight[25]);
	DDX_Control(pDX, IDC_EDIT_HIGHT26, m_hight[26]);
	DDX_Control(pDX, IDC_EDIT_HIGHT27, m_hight[27]);
	DDX_Control(pDX, IDC_EDIT_HIGHT28, m_hight[28]);
	DDX_Control(pDX, IDC_EDIT_HIGHT29, m_hight[29]);
	DDX_Control(pDX, IDC_EDIT_HIGHT30, m_hight[30]);
	DDX_Control(pDX, IDC_EDIT_HIGHT31, m_hight[31]);
	DDX_Control(pDX, IDC_EDIT_HIGHT32, m_hight[32]);

	DDX_Control(pDX, IDC_EDIT_MAPVAL0, m_mapVal[0]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL1, m_mapVal[1]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL2, m_mapVal[2]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL3, m_mapVal[3]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL4, m_mapVal[4]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL5, m_mapVal[5]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL6, m_mapVal[6]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL7, m_mapVal[7]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL8, m_mapVal[8]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL9, m_mapVal[9]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL10, m_mapVal[10]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL11, m_mapVal[11]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL12, m_mapVal[12]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL13, m_mapVal[13]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL14, m_mapVal[14]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL15, m_mapVal[15]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL16, m_mapVal[16]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL17, m_mapVal[17]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL18, m_mapVal[18]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL19, m_mapVal[19]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL20, m_mapVal[20]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL21, m_mapVal[21]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL22, m_mapVal[22]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL23, m_mapVal[23]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL24, m_mapVal[24]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL25, m_mapVal[25]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL26, m_mapVal[26]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL27, m_mapVal[27]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL28, m_mapVal[28]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL29, m_mapVal[29]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL30, m_mapVal[30]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL31, m_mapVal[31]);
	DDX_Control(pDX, IDC_EDIT_MAPVAL32, m_mapVal[32]);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_unit);
	DDX_Control(pDX, IDC_COMBO_LINTYPE, m_mapType);
	DDX_Control(pDX, IDC_COMBO_VESSELTYPE, m_vesselType);
	DDX_Control(pDX, IDC_EDIT_DENSITY, m_editDensity);
	DDX_Control(pDX, IDC_COMBO_FLOWTYPE, m_comboFlowType);
}

//BOOL CMappingEditDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  在此添加额外的初始化
//	
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// 异常: OCX 属性页应返回 FALSE
//}

void CMappingEditDlg::OnCbnSelchangeComboLintype()
{
	int nType;
	nType = m_mapType.GetCurSel();
	m_unit.ResetContent();
	switch(nType)
	{
	case 0:
		m_unit.InsertString(0,_T("m"));	
		m_unit.InsertString(1,_T("ft"));	
		m_unit.InsertString(2,_T("in"));	
		m_unit.InsertString(3,_T("cm"));	
		m_unit.InsertString(4,_T("mm"));
		m_editDensity.EnableWindow(FALSE);
		break;
	case 1:
		m_unit.InsertString(0,_T("kg"));	
		m_unit.InsertString(1,_T("t"));	
		m_unit.InsertString(2,_T("lb"));
		m_editDensity.EnableWindow(TRUE);
		break;
	case 2:
		m_unit.InsertString(0,_T("m3/s"));	
		m_unit.InsertString(1,_T("m3/h"));	
		m_unit.InsertString(2,_T("ft3/s"));	
		m_unit.InsertString(3,_T("ft3/min"));	
		m_unit.InsertString(4,_T("gal/min"));			
		m_unit.InsertString(5,_T("gal/h"));			
		m_unit.InsertString(6,_T("l/s"));			
		m_unit.InsertString(7,_T("l/min"));			
		m_unit.InsertString(8,_T("l/h"));
		m_editDensity.EnableWindow(FALSE);
		
		break;	   						
	case 3:
		m_unit.InsertString(0,_T("m3"));	
		m_unit.InsertString(1,_T("l"));	
		m_unit.InsertString(2,_T("hl"));	
		m_unit.InsertString(3,_T("ft3"));	
		m_unit.InsertString(4,_T("in3"));	
		m_unit.InsertString(5,_T("gal"));
		m_editDensity.EnableWindow(FALSE);
		break;
	}
}

void CMappingEditDlg::OnBnClickedBtnSave()
{
	CProgress progress;
	int intData;

	intData = m_mapType.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x12, UINT8(intData), pointnumber, false);

	intData = m_unit.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x13, UINT8(intData), pointnumber, false);

	intData = m_vesselType.GetCurSel() + 2;
	theApp.m_pClient->SaveData(0x10, UINT8(intData), pointnumber, false);


	CString str;
	m_mapVal[32].GetWindowText(str);
	m_valRatio = (float)_tstof(str);

	theApp.m_pClient->SaveData(0x115, m_valRatio, pointnumber, false);
	theApp.m_pClient->SaveData(0x118, m_valRatio,pointnumber, false);

	if(m_valRatio > 10000.0)
		intData = 0;
	else if(m_valRatio > 1000.0)
		intData = 1;
	else if(m_valRatio > 100.0)
		intData = 2;
	else
		intData = 3;

	theApp.m_pClient->SaveData(0x116, UINT8(intData),pointnumber, false);
	theApp.m_pClient->SaveData(0x119, UINT8(intData),pointnumber, false);

	intData = m_mapType.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x12, UINT8(intData),pointnumber, false);
	theApp.m_pClient->SaveData(0x312, UINT8(intData),pointnumber, false);
	intData = m_unit.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x13, UINT8(intData),pointnumber, false);
	theApp.m_pClient->SaveData(0x313, UINT8(intData),pointnumber, false);


	CArray<float> arrayData;
	
	for (int i = 0; i < 33; i++)
	{
		CString str;
		m_hight[i].GetWindowText(str);
		float f = float((_tstof(str)) / m_hightRatio);
		arrayData.Add(f);
	}

	for (int i = 0; i < 33; i++)
	{
		CString str;
		m_mapVal[i].GetWindowText(str);
		float f = float(_tstof(str) / m_valRatio);
		arrayData.Add(f);
	}
	ASSERT(arrayData.GetSize() == 66);

	theApp.m_pClient->SaveData(0x994, arrayData, pointnumber);
}

void CMappingEditDlg::OnBnClickedButtonResetval()
{
	CString str(_T("0.00"));
	for (int i = 0; i < 33; i++)
	{
		m_hight[i].SetWindowText(str);
		m_mapVal[i].SetWindowText(str);
	}
}

void CMappingEditDlg::OnBnClickedBtnReadfilie()
{
	CFileDialog fileDlg(TRUE, _T(".map"),0 ,4|2 ,_T("Mapping Data Files (*.map)|*.map|"),this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filename(fileDlg.GetPathName());
		CStdioFile file;
		if (file.Open(filename, CFile::modeRead))
		{
			for (int i = 0; i < 33; i++)
			{
				CString str, strHight, strMapVal;
				if (!file.ReadString(str))
					break;
				int dividePos = str.Find(_T("\t"));
				strHight = str.Left(dividePos);
				strMapVal = str.Right(str.GetLength() - dividePos -1);

				m_hight[i].SetWindowText(strHight);
				m_mapVal[i].SetWindowText(strMapVal);
			}
		}
	}

}

void CMappingEditDlg::OnBnClickedBtnSavefile()
{
	CFileDialog fileDlg(FALSE, _T(".map"),0 ,4|2 ,_T("Mapping Data Files (*.map)|*.map|"),this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filename(fileDlg.GetPathName());
		CStdioFile file;
		if (file.Open(filename, CFile::modeWrite | CFile::modeCreate))
		{
			for (int i = 0; i < 33; i++)
			{
				CString strHight, strMapVal;
				m_hight[i].GetWindowText(strHight);
				m_mapVal[i].GetWindowText(strMapVal);
				file.WriteString(strHight + _T("\t") + strMapVal + _T("\n"));
			}
		}
	}
}

int CMappingEditDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create
	m_hightRatio = 0;

	return 0;
}

void CMappingEditDlg::OnBnClickedButtonGenerate()
{
	
	double ratio = 1;
	CString str;

	hightArray.RemoveAll();
	valArray.RemoveAll();

	if (m_hightRatio == 0)
	{
		//float low, high, highPercent, lowPercent;
		
		while(!(theApp.m_pClient->LoadData(0x110, lowPercent, pointnumber)));
		while(!(theApp.m_pClient->LoadData(0x111, low, pointnumber)));
		while(!(theApp.m_pClient->LoadData(0x112, highPercent, pointnumber)));
		while(!(theApp.m_pClient->LoadData(0x113, high, pointnumber)));

		m_hightRatio = (low - high) / (highPercent - lowPercent);
	}

		////////////////////////////ty added///////////////////////////////////////////
switch(m_unit.GetCurSel())//    m3=>other
{
	 case 0:ratio = 1;break;			// m3/s
	 case 1:ratio =3600;break;//m3/h	
 	 case 2:ratio = 35.315;break;//ft3/s
	 case 3:ratio = (35.315*60);break;	// ft3/min
 	 case 4:ratio = (264.172*60);break;	//gal/min
 	 case 5:ratio =  (264.172*3600);break;		// gal/h  "使用 美加仑3.785   英加仑为4.546"		
 	 case 6:ratio = 1000;break;		//l/s
 	 case 7:ratio =  (1000*60);break;		//l/min
	 case 8:ratio =  (1000*3600);break;		//l/h
}




	/////////////////////////ty added/////////////////////////////////////////////////

	switch(m_mapType.GetCurSel())
	{
	case 1:

		m_editDensity.GetWindowText(str);
		if (ratio != 0)
		{
			ratio = _tstof(str);
		}
		
	case 2:
		break;
	case 3:
		switch(m_unit.GetCurSel())//    m3=>other
	/*	{
		case 0:break;			// m3
		case 1:ratio = 1000;break;//l		
		case 2:ratio = 10;break;//hl
		case 3:ratio = 35.315;break;	// ft3
		case 4:ratio = (35.315*1728);break;	// in3
		case 5:ratio = 1000/3.785;break;		// gal/h  "使用 美加仑3.785   英加仑为4.546"		
		}*/

	{
	 case 0:ratio = 1;break;			// m3/s
	 case 1:ratio =3600;break;//m3/h	
 	 case 2:ratio = 35.315;break;//ft3/s
	 case 3:ratio = (35.315*60);break;	// ft3/min
 	 case 4:ratio = (264.172*60);break;	//gal/min
 	 case 5:ratio =  (264.172*3600);break;		// gal/h  "使用 美加仑3.785   英加仑为4.546"		
 	 case 6:ratio = 1000;break;		//l/s
 	 case 7:ratio =  (1000*60);break;		//l/min
	 case 8:ratio =  (1000*3600);break;		//l/h
}

		break;
	default:
		WarnMessageBox(IDS_MAPGENMSG);
		return;
	}
	
	switch(m_vesselType.GetCurSel())
	{
	case 0:
		{// 水平圆筒
			CSpytDlg dlg;
			dlg.P006 = m_hightRatio;
			if (dlg.DoModal() == IDOK)
			{
				dlg.GenerateMapping(hightArray, valArray, m_hightRatio);
				for (int i = 0; i < 33; i++)
				{
					CString str;
					str.Format(_T("%.3f"), hightArray[i]);
					m_hight[i].SetWindowText(str);

					str.Format(_T("%.3f"), valArray[i]*ratio);
					m_mapVal[i].SetWindowText(str);
				}
			}
			break;
		}
	case 1:
		{// 球体
			CQtDlg dlg;
			dlg.P006 = m_hightRatio;
			if (dlg.DoModal() == IDOK)
			{
				dlg.GenerateMapping(hightArray, valArray, m_hightRatio);
				for (int i = 0; i < 33; i++)
				{
					CString str;
					str.Format(_T("%.3f"), hightArray[i]);
					m_hight[i].SetWindowText(str);

					str.Format(_T("%.3f"), valArray[i]*ratio);
					m_mapVal[i].SetWindowText(str);
				}
			}
		}
		break;
	case 2:	// 锥桶
		{
			CZtDlg dlg;
			dlg.P006 = m_hightRatio;
			if (dlg.DoModal() == IDOK)
			{
				dlg.GenerateMapping(hightArray, valArray, m_hightRatio);
				for (int i = 0; i < 33; i++)
				{
					CString str;
					str.Format(_T("%.3f"), hightArray[i]);
					m_hight[i].SetWindowText(str);

					str.Format(_T("%.3f"), valArray[i]*ratio);
					m_mapVal[i].SetWindowText(str);
				}
			}
		}
		break;
	case 3:	
		break;
	case 4:
		// 明渠流量
		switch(m_comboFlowType.GetCurSel())
		{
		case 0:
			{// 巴歇尔
				FlowBaxieer dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR0);
					}
				}
				break;
			}

		case 1:	// 无喉道
			{
				FlowWuhoudao dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR1);
					}
				}
				break;
			}
		case 2:	// 等宽薄壁
			{
				FlowDengkuanbaobi dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR2);
					}
				}
				break;
			}
		case 3:	// 矩形薄壁
			{
				FlowJuxingbaobi dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR3);
					}
				}
				break;
			}
		case 4:	// 矩形宽顶
			{
				FlowJuxingkuanding dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR4);
					}
				}
				break;
			}
		case 5:	// 三角薄壁
			{
				FlowSanjiaobaobi dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR5);
					}
				}
				break;
			}
		case 6:	// 三角剖面
			{
				FlowSanjiaopoumian dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR6);
					}
				}
				break;
			}
		case 7:	// V型
			{
				FlowVxingyan dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR7);
					}
				}
				break;
			}
		case 8:	// 圆缘
			{
				FlowYuanyuan dlg;
				if (dlg.DoModal() == IDOK)
				{
					if (dlg.GenerateMapping(hightArray, valArray, m_hightRatio))
					{
						for (int i = 0; i < 33; i++)
						{
							CString str;
							str.Format(_T("%.3f"), hightArray[i]);
							m_hight[i].SetWindowText(str);

							str.Format(_T("%.3f"), valArray[i]*ratio);
							m_mapVal[i].SetWindowText(str);
						}
					}
					else
					{
						WarnMessageBox(IDS_FLOWERR8);
					}
				}
				break;
			}


		}
		break;
	default:
		break;


	}

}

void CMappingEditDlg::DisplayValue(CArray<float>&val )
{
	CString str;

	//switch(m_unit.GetCurSel())//    m3=>other
	//{
	//case 0:break;			// m3
	//case 1:ratio=1000;break;//l		
	//case 2:ratio=10;break;//hl
	//case 3:ratio=35.315;break;	// ft3
	//case 4:ratio=(35.315*1728);break;	// in3
	//case 5:ratio=3785; break;		// gal/h  "使用 美加仑3.785   英加仑为4.546"		
	//}

	for (int i = 0; i < 33; i++)
	{
		str.Format(_T("%.3f"), val[i] * m_hightRatio);
		m_hight[i].SetWindowText(str);

		str.Format(_T("%.3f"), val[i+33] * m_valRatio);
		m_mapVal[i].SetWindowText(str);
	}

}
void CMappingEditDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	//OnBnClickedBtnLoad();
}

void CMappingEditDlg::OnCbnSelchangeComboVesseltype()
{
	if (m_vesselType.GetCurSel() == 4)
	{
		m_comboFlowType.ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_FLOWTYPE)->ShowWindow(TRUE);
	}
	else
	{
		m_comboFlowType.ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_FLOWTYPE)->ShowWindow(FALSE);
	}
}

void CMappingEditDlg::OnCbnSelchangeComboUnit()
{
 	double ratio = 1;
 
 	switch(m_unit.GetCurSel())//    m3=>other
{
 //	case 0:ratio = 1;break;			// m3
//	case 1:ratio = 1000;break;//l		
 //	case 2:ratio = 10;break;//hl
//	case 3:ratio = 35.315;break;	// ft3
//	case 4:ratio = (35.315*1728);break;	// in3
//	case 5:ratio = 1000/3.785;break;		// gal/h  "使用 美加仑3.785   英加仑为4.546"		
	case 0:ratio = 1;break;			// m3/s
	case 1:ratio =3600;break;//m3/h	
 	case 2:ratio = 35.315;break;//ft3/s
	case 3:ratio = (35.315*60);break;	// ft3/min
	case 4:ratio = (264.172*60);break;	//gal/min
	case 5:ratio =  (264.172*3600);break;		// gal/h  "使用 美加仑3.785   英加仑为4.546"		
	case 6:ratio = 1000;break;		//l/s
	case 7:ratio =  (1000*60);break;		//l/min
	case 8:ratio =  (1000*3600);break;		//l/h

 	}


	for (int i = 0; i < valArray.GetSize(); i++)
{
	CString str;
		str.Format(_T("%.3f"), valArray[i]*ratio);
		m_mapVal[i].SetWindowText(str);
 	}
}
