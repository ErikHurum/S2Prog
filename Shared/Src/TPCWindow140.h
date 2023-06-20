#pragma once
//---------------------------------------------------------------------------
#ifndef TPCWINDOW140H
#define TPCWINDOW140H

class TPCWindow140 :
	public TPCWindow
{
public:
	TPCWindow140(void);
  TPCWindow140(PRogramObject *PRO, int Lower, int Upper, int Main);
	~TPCWindow140(void);
  AnsiString MakeConfigString(int ExtraTabs=0);
  bool LoadConfigString(TSNConfigString &ConfigString);

	U16 MakeWindow(U8 *TxBuf,U16 Ptr, bool Update);

};
#endif
