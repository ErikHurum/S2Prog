#pragma once
//---------------------------------------------------------------------------
#ifndef TPCWINDOW350H
#define TPCWINDOW350H
class TPCWindow350 :
	public TPCWindow
{
public:
	TPCWindow350(void);
  TPCWindow350(PRogramObject *PRO, int Lower, int Upper, int Main);
	~TPCWindow350(void);

	U16 MakeWindow(U8 *TxBuf,U16 Ptr, bool Update);

};
#endif
