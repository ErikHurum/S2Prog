// CalibrationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "CalibrationDlg.h"


// CCalibrationDlg

IMPLEMENT_DYNAMIC(CCalibrationDlg, CDialogEx)

CCalibrationDlg::CCalibrationDlg(CWnd* pParent)
:CDialogEx(IDD_CALIBRATION, pParent), validPoint(0)
{
	for (int i = 0; i < 33; i++)
	{
		m_measuredVal[i] = m_caliVal[i] = 0;
	}
}


BEGIN_MESSAGE_MAP(CCalibrationDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCalibrationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LOAD, &CCalibrationDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_SAVE, &CCalibrationDlg::OnBnClickedSave)
END_MESSAGE_MAP()



// CCalibrationDlg 消息处理程序



void CCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{


	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEASUREDVAL0, m_editMeasuredVal[0]);
	DDX_Control(pDX, IDC_MEASUREDVAL1, m_editMeasuredVal[1]);
	DDX_Control(pDX, IDC_MEASUREDVAL2, m_editMeasuredVal[2]);
	DDX_Control(pDX, IDC_MEASUREDVAL3, m_editMeasuredVal[3]);
	DDX_Control(pDX, IDC_MEASUREDVAL4, m_editMeasuredVal[4]);
	DDX_Control(pDX, IDC_MEASUREDVAL5, m_editMeasuredVal[5]);
	DDX_Control(pDX, IDC_MEASUREDVAL6, m_editMeasuredVal[6]);
	DDX_Control(pDX, IDC_MEASUREDVAL7, m_editMeasuredVal[7]);
	DDX_Control(pDX, IDC_MEASUREDVAL8, m_editMeasuredVal[8]);
	DDX_Control(pDX, IDC_MEASUREDVAL9, m_editMeasuredVal[9]);
	DDX_Control(pDX, IDC_MEASUREDVAL10, m_editMeasuredVal[10]);
	DDX_Control(pDX, IDC_MEASUREDVAL11, m_editMeasuredVal[11]);
	DDX_Control(pDX, IDC_MEASUREDVAL12, m_editMeasuredVal[12]);
	DDX_Control(pDX, IDC_MEASUREDVAL13, m_editMeasuredVal[13]);
	DDX_Control(pDX, IDC_MEASUREDVAL14, m_editMeasuredVal[14]);
	DDX_Control(pDX, IDC_MEASUREDVAL15, m_editMeasuredVal[15]);
	DDX_Control(pDX, IDC_MEASUREDVAL16, m_editMeasuredVal[16]);
	DDX_Control(pDX, IDC_MEASUREDVAL17, m_editMeasuredVal[17]);
	DDX_Control(pDX, IDC_MEASUREDVAL18, m_editMeasuredVal[18]);
	DDX_Control(pDX, IDC_MEASUREDVAL19, m_editMeasuredVal[19]);
	DDX_Control(pDX, IDC_MEASUREDVAL20, m_editMeasuredVal[20]);
	DDX_Control(pDX, IDC_MEASUREDVAL21, m_editMeasuredVal[21]);
	DDX_Control(pDX, IDC_MEASUREDVAL22, m_editMeasuredVal[22]);
	DDX_Control(pDX, IDC_MEASUREDVAL23, m_editMeasuredVal[23]);
	DDX_Control(pDX, IDC_MEASUREDVAL24, m_editMeasuredVal[24]);
	DDX_Control(pDX, IDC_MEASUREDVAL25, m_editMeasuredVal[25]);
	DDX_Control(pDX, IDC_MEASUREDVAL26, m_editMeasuredVal[26]);
	DDX_Control(pDX, IDC_MEASUREDVAL27, m_editMeasuredVal[27]);
	DDX_Control(pDX, IDC_MEASUREDVAL28, m_editMeasuredVal[28]);
	DDX_Control(pDX, IDC_MEASUREDVAL29, m_editMeasuredVal[29]);
	DDX_Control(pDX, IDC_MEASUREDVAL30, m_editMeasuredVal[30]);
	DDX_Control(pDX, IDC_MEASUREDVAL31, m_editMeasuredVal[31]);
	DDX_Control(pDX, IDC_MEASUREDVAL32, m_editMeasuredVal[32]);

	DDX_Control(pDX, IDC_CALIVAL0, m_editCaliVal[0]);
	DDX_Control(pDX, IDC_CALIVAL1, m_editCaliVal[1]);
	DDX_Control(pDX, IDC_CALIVAL2, m_editCaliVal[2]);
	DDX_Control(pDX, IDC_CALIVAL3, m_editCaliVal[3]);
	DDX_Control(pDX, IDC_CALIVAL4, m_editCaliVal[4]);
	DDX_Control(pDX, IDC_CALIVAL5, m_editCaliVal[5]);
	DDX_Control(pDX, IDC_CALIVAL6, m_editCaliVal[6]);
	DDX_Control(pDX, IDC_CALIVAL7, m_editCaliVal[7]);
	DDX_Control(pDX, IDC_CALIVAL8, m_editCaliVal[8]);
	DDX_Control(pDX, IDC_CALIVAL9, m_editCaliVal[9]);
	DDX_Control(pDX, IDC_CALIVAL10, m_editCaliVal[10]);
	DDX_Control(pDX, IDC_CALIVAL11, m_editCaliVal[11]);
	DDX_Control(pDX, IDC_CALIVAL12, m_editCaliVal[12]);
	DDX_Control(pDX, IDC_CALIVAL13, m_editCaliVal[13]);
	DDX_Control(pDX, IDC_CALIVAL14, m_editCaliVal[14]);
	DDX_Control(pDX, IDC_CALIVAL15, m_editCaliVal[15]);
	DDX_Control(pDX, IDC_CALIVAL16, m_editCaliVal[16]);
	DDX_Control(pDX, IDC_CALIVAL17, m_editCaliVal[17]);
	DDX_Control(pDX, IDC_CALIVAL18, m_editCaliVal[18]);
	DDX_Control(pDX, IDC_CALIVAL19, m_editCaliVal[19]);
	DDX_Control(pDX, IDC_CALIVAL20, m_editCaliVal[20]);
	DDX_Control(pDX, IDC_CALIVAL21, m_editCaliVal[21]);
	DDX_Control(pDX, IDC_CALIVAL22, m_editCaliVal[22]);
	DDX_Control(pDX, IDC_CALIVAL23, m_editCaliVal[23]);
	DDX_Control(pDX, IDC_CALIVAL24, m_editCaliVal[24]);
	DDX_Control(pDX, IDC_CALIVAL25, m_editCaliVal[25]);
	DDX_Control(pDX, IDC_CALIVAL26, m_editCaliVal[26]);
	DDX_Control(pDX, IDC_CALIVAL27, m_editCaliVal[27]);
	DDX_Control(pDX, IDC_CALIVAL28, m_editCaliVal[28]);
	DDX_Control(pDX, IDC_CALIVAL29, m_editCaliVal[29]);
	DDX_Control(pDX, IDC_CALIVAL30, m_editCaliVal[30]);
	DDX_Control(pDX, IDC_CALIVAL31, m_editCaliVal[31]);
	DDX_Control(pDX, IDC_CALIVAL32, m_editCaliVal[32]);

}

void CCalibrationDlg::OnBnClickedOk()
{
	for (int i = 0; i < 33; i++)
	{
		CString str;
		m_editMeasuredVal[i].GetWindowText(str);
		m_measuredVal[i] = float(_tstof(str));

		m_editCaliVal[i].GetWindowText(str);
		m_caliVal[i] = float(_tstof(str));
	}
	OnOK();
}

void CCalibrationDlg::OnBnClickedLoad()
{
	CFileDialog fileDlg(TRUE, _T(".csv"),0 ,4|2 ,_T("Calibration Data Files (*.csv)|*.csv|"),this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filename(fileDlg.GetPathName());
		CStdioFile file;
		if (file.Open(filename, CFile::modeRead))
		{
			for (int i = 0; i < 33; i++)
			{
				CString str, measuredVal, caliVal;
				if (!file.ReadString(str))
					break;
				int dividePos = str.Find(_T("\t"));
				measuredVal = str.Left(dividePos);
				caliVal = str.Right(str.GetLength() - dividePos -1);

				m_editMeasuredVal[i].SetWindowText(measuredVal);
				m_editCaliVal[i].SetWindowText(caliVal);
			}
		}
	}
}

void CCalibrationDlg::OnBnClickedSave()
{
	CFileDialog fileDlg(FALSE, _T(".csv"),0 ,4|2 ,_T("Calibration Data Files (*.csv)|*.csv|"),this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filename(fileDlg.GetPathName());
		CStdioFile file;
		if (file.Open(filename, CFile::modeWrite | CFile::modeCreate))
		{
			for (int i = 0; i < 33; i++)
			{
				CString measuredVal, caliVal;
				m_editMeasuredVal[i].GetWindowText(measuredVal);
				m_editCaliVal[i].GetWindowText(caliVal);
				file.WriteString(measuredVal + _T("\t") + caliVal + _T("\n"));
			}
		}
	}
}

BOOL CCalibrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	for (int i = validPoint; i < 33; i++)
	{
		m_editMeasuredVal[i].EnableWindow(false);
		m_editCaliVal[i].EnableWindow(false);
	}

	for (int i = 0; i < validPoint ; i++)
	{
		CString s;
		s.Format(_T("%.3f"), m_measuredVal[i]);
		m_editMeasuredVal[i].SetWindowText(s);

		s.Format(_T("%.3f"), m_caliVal[i]);
		m_editCaliVal[i].SetWindowText(s);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
