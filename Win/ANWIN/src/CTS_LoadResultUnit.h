//---------------------------------------------------------------------------

#ifndef CTS_LoadResultUnitH
#define CTS_LoadResultUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LoadResultWin.h"
#include "QRCtrls.hpp"
#include "qrpBaseCtrls.hpp"
#include "qrpctrls.hpp"
#include "QuickRpt.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
//---------------------------------------------------------------------------
class TLoadResultForm1 : public TLoadResultForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TLoadResultForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoadResultForm1 *LoadResultForm1;
//---------------------------------------------------------------------------
#endif
