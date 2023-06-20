#pragma once
//---------------------------------------------------------------------------
#ifndef TPCWINDOW196H
#define TPCWINDOW1960H

class TPCWindow196 :
	public TPCWindow
{
public:
	TPCWindow196(void);
  TPCWindow196(PRogramObject *PRO, int Lower, int Upper, int Main);
	~TPCWindow196(void);
	U16 MakeWindow(U8 *TxBuf,U16 Ptr, bool Update);
  AnsiString MakeConfigString(int ExtraTabs=0);
  bool LoadConfigString(TSNConfigString &ConfigString);
};
#endif
