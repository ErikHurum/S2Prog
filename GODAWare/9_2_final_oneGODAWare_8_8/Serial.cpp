#include "StdAfx.h"
#include "Serial.h"



CSerial::CSerial(void)
{
	OVERTIME = 500;
}

CSerial::~CSerial(void)
{

}



int CSerial::Write(const BYTE * bytes, int bytesToWrite)
{

	return m_sp.Write(bytes, bytesToWrite);
}

int CSerial::Read(BYTE * bytes, int bytesToRead)
{
	if (bytes==NULL || bytesToRead<=0)
	{
		return 0;
	}

//	if (!m_sp.DataWaiting(3000))
//	{
//		TRACE("3s无数据\n");
//		return 0;
//	};

	
	int bytesRead = 0;
	DWORD endTime = GetTickCount() + OVERTIME;
	while (bytesToRead>0)
	{
		int result = m_sp.Read(bytes+bytesRead, bytesToRead);

		bytesRead += result;
		bytesToRead -= result;

		if (result<0)
		{
			return bytesRead;
		}
		else	if (bytesToRead==0)
		{
			return bytesRead;
		}
		else if ( result>0 )
		{
			endTime = GetTickCount() + OVERTIME;
		}
		else if ( GetTickCount() > endTime )
		{
			TRACE("读取时超时\n");
			return bytesRead;
		}

		::Sleep(OVERTIME/10);
	}

	return bytesRead;

}
