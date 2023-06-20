// ClientThread.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "ClientThread.h"

extern CMutex socketMutex;
extern float gNullHight[3];

//const UINT WM_SETSOCKET = ::RegisterWindowMessage(_T("SetSocket"));
//extern const UINT WM_CLOSESOCKET = ::RegisterWindowMessage(_T("CloseSocket"));

bool load3Hights;

extern CErrCounter errCounter;

// CClientThreadWnd
BEGIN_MESSAGE_MAP(CClientThreadWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CClientThread

IMPLEMENT_DYNCREATE(CClientThread, CWinThread)

CClientThread::CClientThread()
{
}

CClientThread::~CClientThread()
{
}

BOOL CClientThread::InitInstance()
{
	m_pMainWnd = new CClientThreadWnd;
	AfxSocketInit();
	return TRUE;
}

int CClientThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CClientThread, CWinThread)

END_MESSAGE_MAP()



// CClientThread 消息处理程序

void CClientThreadWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值



	bool success = true;

	const int dataId = 0x990;

	if(!load3Hights)
	// 从Server读取数据
	{
		CPacket pa;
		pa.cmdID = LOAD_CMD;
		pa.dataID = dataId;
		pa.sensorID = 0;
		if ( !theApp.m_pServer->SendCommand(pa) )
		{
			TRACE("Load from 0x%x failed. \n", dataId);
			
			success = false;
			goto quit;

		}

		if (pa.cmdID!=LOAD_OK)
		{
			TRACE("Load from 0x%x failed. \n", dataId);

			success = false;
			goto quit;

		}

		if (pa.data.GetSize() != 4)
		{
			TRACE("Load from 0x%x failed. \n", dataId);
			success = false;
			goto quit;
		}

		BYTE d[4];
		d[0] = pa.data[0];
		d[1] = pa.data[1];
		d[2] = pa.data[2];
		d[3] = pa.data[3];

		gNullHight[0] = *((float*)d);

		TRACE("Load %f from 0x%x\n", gNullHight[0], pa.dataID);
	}
	else
	{
		CPacket pa;
		//for (int i = 0; i < 3; i++)
		{
			static int i = 0;
			pa.cmdID = LOAD_CMD;
			pa.dataID = dataId;
			pa.sensorID = i;
			if (!theApp.m_pServer->SendCommand(pa))
			{
				success = false;
				goto quit;
			}

			if (pa.cmdID != LOAD_OK)
			{
				success = false;
				goto quit;
			}
			if (pa.data.GetSize() != 4)
			{
				success = false;
				goto quit;
			}
			BYTE d[4];
			d[0] = pa.data[0];
			d[1] = pa.data[1];
			d[2] = pa.data[2];
			d[3] = pa.data[3];

			gNullHight[i] = *((float*)d);
			i++;
			i%=3;
		}

	}


quit:


	errCounter.SetErr(success);


	CFrameWnd::OnTimer(nIDEvent);


}

int CClientThreadWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer(1, 20000, NULL);
	
	return 0;

}