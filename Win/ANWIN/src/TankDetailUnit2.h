//---------------------------------------------------------------------------

#ifndef TankDetailUnit2H
#define TankDetailUnit2H
#include "ChildUnit.h"
#include <Data.DB.hpp>
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TTankDetailsForm2 : public TChildForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TPaintBox *PaintBox1;
	TTabSheet *TabSheet2;
	TDBGrid *DBGrid1;
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TTankDetailsForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankDetailsForm2 *TankDetailsForm2;
//---------------------------------------------------------------------------
#endif
