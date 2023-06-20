// CServerUI.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC.h"
#include "ServerUI.h"


// CServerUI �Ի���

IMPLEMENT_DYNAMIC(CServerUI, CDialog)

CServerUI::CServerUI(CWnd* pParent /*=NULL*/)
	: CDialog(CServerUI::IDD, pParent)
{

}

CServerUI::~CServerUI()
{
}

void CServerUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerUI, CDialog)
ON_MESSAGE(WM_USERCONNECTED, OnUserConnected)
ON_MESSAGE(WM_USERDISCONNECTED, OnUserDisconnected)
END_MESSAGE_MAP()


// CServerUI ��Ϣ�������

BOOL CServerUI::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	WCHAR IPStr[16];
	for (int i=0;i<16;i++)
		IPStr[i] = 0;
	GetIP(IPStr);
	GetDlgItem(IDC_STATIC_IP)->SetWindowText(IPStr);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CServerUI::GetIP(WCHAR * Hostaddress)
{
	if ( !Hostaddress )
		return FALSE;

	//ȡ����IP��ַ
	struct hostent *pHostEnt;
	char hostname[30];
	gethostname(hostname,30);
	pHostEnt = gethostbyname( hostname);//��ñ���IP

	// added for multiple IP
	// start
	int nIP = 0;
	char **pptr = pHostEnt->h_addr_list;
	while(*pptr!=NULL) {
		nIP++;
		pptr++;
	}

	if(nIP<=0) {
		return FALSE;
	}
	else if(nIP==1) {
		wsprintf( Hostaddress, _T("%d.%d.%d.%d"),
			( pHostEnt->h_addr_list[0][0] & 0x00ff ),
			( pHostEnt->h_addr_list[0][1] & 0x00ff ),
			( pHostEnt->h_addr_list[0][2] & 0x00ff ),
			( pHostEnt->h_addr_list[0][3] & 0x00ff ) );
	}
	else {
		// ����IP������
		// 10.x.x.x
		// 172.16.x.x �� 172.31.x.x
		// 192.168.x.x
		int num0 = 0;
		int num1 = 0;
		for(int i=0;i<nIP;i++) {
			num0 = pHostEnt->h_addr_list[i][0] & 0x00ff;
			num1 = pHostEnt->h_addr_list[i][1] & 0x00ff;
			if(i==nIP-1) {
				wsprintf( Hostaddress, _T("%d.%d.%d.%d"),
					( pHostEnt->h_addr_list[i][0] & 0x00ff ),
					( pHostEnt->h_addr_list[i][1] & 0x00ff ),
					( pHostEnt->h_addr_list[i][2] & 0x00ff ),
					( pHostEnt->h_addr_list[i][3] & 0x00ff ) );
				break;
			}
			if(num0==10)
				continue;
			if(num0==172 && num1>=16 && num1<=31)
				continue;
			if(num0==192 && num1==168)
				continue;
			wsprintf( Hostaddress, _T("%d.%d.%d.%d"),
				( pHostEnt->h_addr_list[i][0] & 0x00ff ),
				( pHostEnt->h_addr_list[i][1] & 0x00ff ),
				( pHostEnt->h_addr_list[i][2] & 0x00ff ),
				( pHostEnt->h_addr_list[i][3] & 0x00ff ) );
			break;
		}
	}
	// end
	// added for multiple IP

	return TRUE;
}

LRESULT CServerUI::OnUserConnected( WPARAM wParam, LPARAM lPARAM )
{
	if ( wParam!=0 || lPARAM!=0 )
		return FALSE;

	GetDlgItem(IDC_STATIC_USERSTATUS)->SetWindowText(_T("�û�������"));

	return TRUE;
}

LRESULT CServerUI::OnUserDisconnected( WPARAM wParam, LPARAM lPARAM )
{
	if ( wParam!=0 || lPARAM!=0 )
		return FALSE;

	GetDlgItem(IDC_STATIC_USERSTATUS)->SetWindowText(_T("�û�δ����"));

	return TRUE;
}