#pragma once

#if defined _DEBUG
#include <stdio.h> /* vsprintf */


static inline void DMT_TRACE(const char *fmt, ...)
{
	const size_t DPRINTF_BUF_SZ = 1024;
	
	va_list args;
	char buf[DPRINTF_BUF_SZ];
	va_start(args, fmt);
	
	vsprintf_s(buf, fmt, args);

	CString s(buf);
	CStdioFile f;

	f.Open(_T("log.txt"),CFile::modeReadWrite|CFile::modeNoTruncate|CFile::modeCreate);

	CTime time = CTime::GetCurrentTime();///构造CTime对象
	CString m_strTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));

	f.SeekToEnd();
	f.WriteString(m_strTime);
	f.WriteString(_T(" "));
	f.WriteString(s);
	f.WriteString(_T("\n"));


	f.Close();
}
#else
static inline void DMT_TRACE(char *, ...) {}

#endif

