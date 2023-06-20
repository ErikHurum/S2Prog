//---------------------------------------------------------------------------

#ifndef TankDetailUnit2H
#define TankDetailUnit2H
#include "ChildUnit.h"

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "LiteCall.hpp"
#include "MemDS.hpp"
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include "DASQLMonitor.hpp"
#include "LiteSQLMonitor.hpp"
//---------------------------------------------------------------------------
class TTankDetailsForm2 : public TChildForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TPaintBox *PaintBox1;
	TTabSheet *TabSheet2;
	TLiteConnection *LiteConnection1;
	TLiteTable *LiteTable1;
	TDBGrid *DBGrid1;
	TLiteDataSource *LiteDataSource1;
	TLiteSQLMonitor *LiteSQLMonitor1;
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
