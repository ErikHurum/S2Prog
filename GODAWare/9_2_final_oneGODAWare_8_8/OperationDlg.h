#pragma once


// COperationDlg
// ���н����Ǳ�����ĶԻ���Ļ���

class COperationDlg : public CCustomDialogEx
{
	DECLARE_DYNAMIC(COperationDlg)

public:
	COperationDlg();
	virtual ~COperationDlg();

	virtual void LoadData() = 0;	// ��ȡ��ǰ�Ի����ڵ�����
	virtual void SaveData() = 0;	// �洢��ǰ�Ի����ڵ�����

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


