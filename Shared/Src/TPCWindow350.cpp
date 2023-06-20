#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------


TPCWindow350::TPCWindow350(void)
{
}

TPCWindow350::TPCWindow350(PRogramObject *PRO, int Lower, int Upper, int Main):
TPCWindow(PRO, Lower, Upper, Main)
{
}

TPCWindow350::~TPCWindow350(void)
{
}
//---------------------------------------------------------------------------



U16 TPCWindow350::MakeWindow(U8 *TxBuf,U16 Ptr, bool Update)
{
  return Ptr;

}

