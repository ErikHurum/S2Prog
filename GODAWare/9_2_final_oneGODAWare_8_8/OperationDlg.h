#pragma once


// COperationDlg
// 所有进行仪表操作的对话框的基类

class COperationDlg : public CCustomDialogEx
{
	DECLARE_DYNAMIC(COperationDlg)

public:
	COperationDlg();
	virtual ~COperationDlg();

	virtual void LoadData() = 0;	// 读取当前对话框内的数据
	virtual void SaveData() = 0;	// 存储当前对话框内的数据

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();

private:
	CFont font;
protected:
	virtual void OnOK();
	virtual void OnCancel();
};


