#pragma once
#ifndef PVCSSCREENINFO_H_
#define PVCSSCREENINFO_H_

#include "PvcsFrame.h"
#include "pvcsscreenthread.h"
#include <vector>

class CPvcsScreenInfo
{
public:
	CPvcsScreenInfo(void);
	~CPvcsScreenInfo(void);
public:
	static vector<CPvcsScreenInfo*> m_vecScreenInfo;
	CPvcsFrame * m_ptrScreenFrame;
	bool m_bCommandStatus;
	CString m_strCommandingMachineIP;
	CString m_strScreenTitle;
	CPvcsScreenThread *m_ptrScreenThread;
	bool m_bScreenClose;
};
#endif