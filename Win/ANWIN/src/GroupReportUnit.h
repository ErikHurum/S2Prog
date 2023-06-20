//---------------------------------------------------------------------------

#ifndef GroupReportUnitH
#define GroupReportUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "ChildUnit.h"
//---------------------------------------------------------------------------

class TGroupTablePic;

//---------------------------------------------------------------------------
class TGroupReportForm : public TChildForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGridTanks;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
  vector<PRogramObjectBase*> TankVector;
  vector<int>ValueIdVector;
	void __fastcall UpdateStringGrid(void);

public:		// User declarations
  __fastcall TGroupReportForm(TComponent* Owner);
  TStringGrid *ActiveStringGrid;
  void __fastcall SetMiscVectors(vector<PRogramObjectBase*> ObjVector,vector<int>ValIdVector);


};
//---------------------------------------------------------------------------
extern PACKAGE TGroupReportForm *GroupReportForm;
//---------------------------------------------------------------------------
#endif
